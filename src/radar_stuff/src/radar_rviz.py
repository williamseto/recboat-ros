#!/usr/bin/env python

# Import the required packages
import sys # Command Line Arguments
import cv2  # OpenCV bindings
import rospy # ROS Python bindings
from sensor_msgs.msg import Image # Image Sensor msg 
from cv_bridge import CvBridge, CvBridgeError # cv_bridge ros_image <-> opencv_image
from std_msgs.msg import Float64, Float32
import math
from std_msgs.msg import UInt8MultiArray
import numpy as np
from scipy.interpolate import interp1d
from scipy.ndimage import map_coordinates
from span_pose.msg import span_pose

from visualization_msgs.msg import Marker
from geometry_msgs.msg import Point

'''
`render_map` is class to render radar data from the radar
on the map.
'''

def conv_angle(f):
    if f < 0:
        return f + (2*np.pi)
    else:
        return f

conv_angle = np.vectorize(conv_angle)

class render_map:
	def __init__(self):
		self.image_pub = rospy.Publisher("radar_2_map_im", Image, queue_size=1)
		self.image_sub = rospy.Subscriber("raw_radar_image", UInt8MultiArray, self.callback, queue_size=1)
		self.pose_sub = rospy.Subscriber("recboat/span_pose", span_pose, self.callback_pose, queue_size=1)
		#self.im_map_const = cv2.imread("highres_new.bmp")
		self.lat = 0
		self.lon = 0
		self.yaw = 0
		self.north = 0
		self.east = 0

		self.radardata = np.array([0])

		##### VISUALIZATION #####
		self.viz_pub = rospy.Publisher('visualization_marker', Marker, queue_size=1)
		marker = Marker()
		marker.header.frame_id = "/map"
		marker.header.stamp = rospy.Time.now()
		marker.type = marker.POINTS
		marker.action = marker.ADD
		marker.scale.x = 1.0
		marker.scale.y = 1.0
		marker.scale.z = 0.0

		marker.color.a = 1.0
		marker.color.r = 1.0
		marker.color.g = 0.0
		marker.color.b = 0.0

		marker.pose.orientation.w = 1.0
		marker.pose.position.x = 0.0
		marker.pose.position.y = 0.0
		marker.pose.position.z = 0.0
		marker.lifetime = rospy.Duration()

		self.marker = marker
		##############################

	def callback_pose(self, data):
		self.lat = data.lat
		self.lon = data.lon
		self.yaw = data.yaw
		self.north = data.north
		self.east = data.east

	def callback(self, data):

		new_data = map(ord, data.data)

		if len(new_data) != 1048576:
		    return

		z = np.array(new_data, dtype=float).reshape(2048, 512)

		deg_per_spoke = float(360) / 2048
		#adjust for heading

		yaw_deg = self.yaw * 180 / np.pi

		num_roll = int(round( (yaw_deg / deg_per_spoke) ))
		z = np.roll(z, num_roll, axis=0)

		#set last column to 0
		z[:, -1] = 0

		self.radardata = z

		
def main(args):


	br = CvBridge()
	# Initialize the node
	rospy.init_node('radar_2_map', anonymous="True")

	ic = render_map()

	radar_range = 125.

	#define polar grid
	nr = 512    
	nt = 2048

	r = np.linspace(0., radar_range, nr)
	t = np.linspace(0., 2*np.pi, nt)


	### TODO: figure out correct scale
	# Define new cartesian grid
	nx = 225
	ny = 225

	#1 meter resolution
	x = np.linspace(-125, 125, nx)
	y = np.linspace(-125, 125, ny)


	#map our cartesian grid to r, theta values
	X, Y = np.meshgrid(x, y)

	cart_r = np.sqrt(X*X+Y*Y)
	cart_t = np.arctan2(Y, X)

	cart_t = conv_angle(cart_t)  #convert angles to [0, 2pi]



	#interpolate our converted cartesian grid into indices of the radar data matrix
	ir = interp1d(r, np.arange(len(r)), bounds_error=False)
	it = interp1d(t, np.arange(len(t)))

	new_ir = ir(cart_r.ravel())
	new_it = it(cart_t.ravel())
	coords = np.array([new_it, new_ir])

	while not rospy.is_shutdown():
		if ic.radardata.shape == (2048,512):

			img = map_coordinates(ic.radardata, coords, order=0).reshape(cart_r.shape)


			#world file/map constants
			ori_x = 581007.941672
			ori_y = 4481948.597665
			grid_size = 4.065041
			map_pix_height = 1968


			boat_x = (ic.east - ori_x)/grid_size
			boat_y = map_pix_height + (ic.north - ori_y)/grid_size

			#im_map = ic.im_map_const.copy()

			#print im_map.shape
			#print img.shape
			
			'''
			for i in range(-100, 100):
				for j in range(-100, 100):
					if img[100+j, 100+i] > 0:
						im_map[p_j+j, p_i+i, 1:3] = 0
						im_map[p_j+j, p_i+i, 0] = 255

			'''
			
			ic.marker.points = []
			
			for i in range(-nx/2, nx/2):
				for j in range(-nx/2, nx/2):

					if img[nx/2+j, nx/2+i] > 0:
						p = Point() 
						p.x = boat_x + j
						p.y = boat_y + i
						p.z = 0.0

						ic.marker.points.append(p)
			'''
			p = Point() 
			p.x = boat_x
			p.y = boat_y
			p.z = 0.0
			'''
			ic.marker.points.append(p)
			ic.viz_pub.publish(ic.marker)

			#cv2.namedWindow("Image", cv2.WINDOW_NORMAL)
			#cv2.imshow("image", img)
	        #cv2.waitKey(1)
	        

			#ic.image_pub.publish(br.cv2_to_imgmsg(im_map, "bgr8"))


if __name__ == "__main__":

	main(sys.argv)
