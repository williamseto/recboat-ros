#!/usr/bin/env python

# Import the required packages
import sys # Command Line Arguments
import cv2  # OpenCV bindings
import rospy # ROS Python bindings
from sensor_msgs.msg import Image # Image Sensor msg 
from cv_bridge import CvBridge, CvBridgeError # cv_bridge ros_image <-> opencv_image
from std_msgs.msg import Float64, Float32
import math

'''
`render_map` is class to render radar data from the radar
on the map.
'''
class render_map:
	def __init__(self):
		self.image_pub = rospy.Publisher("radar_2_map_im", Image, queue_size=1)
		self.bridge = CvBridge()
		self.image_sub = rospy.Subscriber("radar_raw_will", Image, self.callback, queue_size=1)
		self.lat_sub = rospy.Subscriber("boat_lat", Float64, self.callback_lat, queue_size=1)
		self.lon_sub = rospy.Subscriber("boat_lon", Float64, self.callback_lon, queue_size=1)
		self.yaw_sub = rospy.Subscriber("boat_yaw", Float32, self.callback_yaw, queue_size=1)
		self.im_map_const = cv2.imread("../../map/map_bri.bmp")
		self.lat = 0;
		self.lon = 0;
		self.yaw = 0;

	def callback_lat(self, data):
		self.lat = data.data;
	def callback_lon(self, data):
		self.lon = data.data;

	def callback_yaw(self, data):
		self.yaw = data.data;

	def callback(self, data):
		try:	
			im_radar = self.bridge.imgmsg_to_cv2(data, "bgr8")
		except CvBridgeError as e:
			print(e)
		# grab the dimensions of the image and calculate the center
		# of the image
		(h, w) = im_radar.shape[:2]
		center = (w / 2, h / 2)
		
		# Rotate the image by 180 degrees
		print self.yaw
		M = cv2.getRotationMatrix2D(center, -math.degrees(self.yaw), 1.0)
		im_rotated = cv2.warpAffine(im_radar, M, (w, h))
		
		# Rescale according to the size of the map
		#im_rotated = cv2.resize(im_rotated, (100, 100))
		# Get the height and width of the rotated image
		(h, w) = im_rotated.shape[:2]

		p_i, p_j = (80.021197 + self.lon)/0.000043, (40.474416 - self.lat)/0.000043
		# Render the plot on the map
		im_map = self.im_map_const.copy()
		for i in range(-w/2,w/2):
			for j in range(-h/2,h/2):
				if im_rotated[h/2+j, w/2+i, 0] > 0:
					im_map[p_j+j, p_i+i, 1:3] = 0
					im_map[p_j+j, p_i+i, 0] = 255
		#cv2.namedWindow("Image", cv2.WINDOW_NORMAL);
		#cv2.imshow("Image", im_map)
		try:
			# Publish the image
			self.image_pub.publish(self.bridge.cv2_to_imgmsg(im_map, "bgr8"))
		except CvBridgeError as e:
			print(e)
			
		
def main(args):
	# Create the render_map object
	ic = render_map()
	# Initialize the node
	rospy.init_node('radar_2_map', anonymous="True")
	try:
		rospy.spin()
	except KeyboardInterrupt:
		print "Shutting down"	

if __name__ == "__main__":
	main(sys.argv)
