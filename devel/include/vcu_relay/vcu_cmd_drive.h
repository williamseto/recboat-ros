// Generated by gencpp from file vcu_relay/vcu_cmd_drive.msg
// DO NOT EDIT!


#ifndef VCU_RELAY_MESSAGE_VCU_CMD_DRIVE_H
#define VCU_RELAY_MESSAGE_VCU_CMD_DRIVE_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>

namespace vcu_relay
{
template <class ContainerAllocator>
struct vcu_cmd_drive_
{
  typedef vcu_cmd_drive_<ContainerAllocator> Type;

  vcu_cmd_drive_()
    : header()
    , port(0.0)
    , stbd(0.0)
    , steer(0.0)  {
    }
  vcu_cmd_drive_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , port(0.0)
    , stbd(0.0)
    , steer(0.0)  {
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef float _port_type;
  _port_type port;

   typedef float _stbd_type;
  _stbd_type stbd;

   typedef float _steer_type;
  _steer_type steer;




  typedef boost::shared_ptr< ::vcu_relay::vcu_cmd_drive_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::vcu_relay::vcu_cmd_drive_<ContainerAllocator> const> ConstPtr;

}; // struct vcu_cmd_drive_

typedef ::vcu_relay::vcu_cmd_drive_<std::allocator<void> > vcu_cmd_drive;

typedef boost::shared_ptr< ::vcu_relay::vcu_cmd_drive > vcu_cmd_drivePtr;
typedef boost::shared_ptr< ::vcu_relay::vcu_cmd_drive const> vcu_cmd_driveConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::vcu_relay::vcu_cmd_drive_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::vcu_relay::vcu_cmd_drive_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace vcu_relay

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': True}
// {'std_msgs': ['/opt/ros/jade/share/std_msgs/cmake/../msg'], 'vcu_relay': ['/home/bikramjothanzra/recboat-ros/src/vcu_relay/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::vcu_relay::vcu_cmd_drive_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::vcu_relay::vcu_cmd_drive_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::vcu_relay::vcu_cmd_drive_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::vcu_relay::vcu_cmd_drive_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::vcu_relay::vcu_cmd_drive_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::vcu_relay::vcu_cmd_drive_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::vcu_relay::vcu_cmd_drive_<ContainerAllocator> >
{
  static const char* value()
  {
    return "571248e59ce03d7b264828ab2e3411c3";
  }

  static const char* value(const ::vcu_relay::vcu_cmd_drive_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x571248e59ce03d7bULL;
  static const uint64_t static_value2 = 0x264828ab2e3411c3ULL;
};

template<class ContainerAllocator>
struct DataType< ::vcu_relay::vcu_cmd_drive_<ContainerAllocator> >
{
  static const char* value()
  {
    return "vcu_relay/vcu_cmd_drive";
  }

  static const char* value(const ::vcu_relay::vcu_cmd_drive_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::vcu_relay::vcu_cmd_drive_<ContainerAllocator> >
{
  static const char* value()
  {
    return "Header header\n\
\n\
float32 port\n\
float32 stbd\n\
float32 steer\n\
\n\
================================================================================\n\
MSG: std_msgs/Header\n\
# Standard metadata for higher-level stamped data types.\n\
# This is generally used to communicate timestamped data \n\
# in a particular coordinate frame.\n\
# \n\
# sequence ID: consecutively increasing ID \n\
uint32 seq\n\
#Two-integer timestamp that is expressed as:\n\
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')\n\
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')\n\
# time-handling sugar is provided by the client library\n\
time stamp\n\
#Frame this data is associated with\n\
# 0: no frame\n\
# 1: global frame\n\
string frame_id\n\
";
  }

  static const char* value(const ::vcu_relay::vcu_cmd_drive_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::vcu_relay::vcu_cmd_drive_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.port);
      stream.next(m.stbd);
      stream.next(m.steer);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER;
  }; // struct vcu_cmd_drive_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::vcu_relay::vcu_cmd_drive_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::vcu_relay::vcu_cmd_drive_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "port: ";
    Printer<float>::stream(s, indent + "  ", v.port);
    s << indent << "stbd: ";
    Printer<float>::stream(s, indent + "  ", v.stbd);
    s << indent << "steer: ";
    Printer<float>::stream(s, indent + "  ", v.steer);
  }
};

} // namespace message_operations
} // namespace ros

#endif // VCU_RELAY_MESSAGE_VCU_CMD_DRIVE_H
