  #include "markerrviz.h"
  
  ros::Publisher MarkerRVIZ::markerPub;
  MarkerRVIZ :: MarkerRVIZ(ros::NodeHandle *nodeHandle, std::string ns, std::string frameID, MarkerType markerType, float red, float blue, float green)
  {
        markerPub = nodeHandle->advertise<visualization_msgs::Marker>("visualization_marker", 1);
        
        pointMarker.header.frame_id = "/" + frameID;
        pointMarker.header.stamp = ros::Time::now();
        pointMarker.ns = ns;
        pointMarker.action = visualization_msgs::Marker::ADD;

        pointMarker.id = 0;
        switch (markerType)
        {
            case POINTS : pointMarker.type = visualization_msgs::Marker::POINTS;
            break;
            case LINE_STRIP : pointMarker.type = visualization_msgs::Marker::LINE_STRIP;
            std::cout<<"\n\n\nLineStrip\n\n\n";
            break;
            case LINE_LIST : pointMarker.type = visualization_msgs::Marker::LINE_LIST;
            break;
        }
        

        pointMarker.color.r = red;
        pointMarker.color.g = blue;
        pointMarker.color.b = green;
        pointMarker.color.a = 1.0;

        pointMarker.scale.x = 5;
        pointMarker.scale.y = 5;
        pointMarker.scale.z = 0.01;

        pointMarker.lifetime = ros::Duration();
  }  
  
   void MarkerRVIZ :: UpdateGUI(double x, double y, double z)
    {   
        p.x = x;
        p.y = y;
        p.z = z;
        pointMarker.points.push_back(p);
        markerPub.publish(pointMarker);
    }
    
    void MarkerRVIZ :: ClearMarker()
    {
        pointMarker.points.clear(); 
    }