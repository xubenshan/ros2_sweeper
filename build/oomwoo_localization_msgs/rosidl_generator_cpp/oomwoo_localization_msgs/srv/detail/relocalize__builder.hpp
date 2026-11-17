// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from oomwoo_localization_msgs:srv/Relocalize.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "oomwoo_localization_msgs/srv/relocalize.hpp"


#ifndef OOMWOO_LOCALIZATION_MSGS__SRV__DETAIL__RELOCALIZE__BUILDER_HPP_
#define OOMWOO_LOCALIZATION_MSGS__SRV__DETAIL__RELOCALIZE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "oomwoo_localization_msgs/srv/detail/relocalize__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace oomwoo_localization_msgs
{

namespace srv
{


}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::oomwoo_localization_msgs::srv::Relocalize_Request>()
{
  return ::oomwoo_localization_msgs::srv::Relocalize_Request(rosidl_runtime_cpp::MessageInitialization::ZERO);
}

}  // namespace oomwoo_localization_msgs


namespace oomwoo_localization_msgs
{

namespace srv
{

namespace builder
{

class Init_Relocalize_Response_message
{
public:
  explicit Init_Relocalize_Response_message(::oomwoo_localization_msgs::srv::Relocalize_Response & msg)
  : msg_(msg)
  {}
  ::oomwoo_localization_msgs::srv::Relocalize_Response message(::oomwoo_localization_msgs::srv::Relocalize_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::oomwoo_localization_msgs::srv::Relocalize_Response msg_;
};

class Init_Relocalize_Response_runtime_s
{
public:
  explicit Init_Relocalize_Response_runtime_s(::oomwoo_localization_msgs::srv::Relocalize_Response & msg)
  : msg_(msg)
  {}
  Init_Relocalize_Response_message runtime_s(::oomwoo_localization_msgs::srv::Relocalize_Response::_runtime_s_type arg)
  {
    msg_.runtime_s = std::move(arg);
    return Init_Relocalize_Response_message(msg_);
  }

private:
  ::oomwoo_localization_msgs::srv::Relocalize_Response msg_;
};

class Init_Relocalize_Response_confidence
{
public:
  explicit Init_Relocalize_Response_confidence(::oomwoo_localization_msgs::srv::Relocalize_Response & msg)
  : msg_(msg)
  {}
  Init_Relocalize_Response_runtime_s confidence(::oomwoo_localization_msgs::srv::Relocalize_Response::_confidence_type arg)
  {
    msg_.confidence = std::move(arg);
    return Init_Relocalize_Response_runtime_s(msg_);
  }

private:
  ::oomwoo_localization_msgs::srv::Relocalize_Response msg_;
};

class Init_Relocalize_Response_score_normalized
{
public:
  explicit Init_Relocalize_Response_score_normalized(::oomwoo_localization_msgs::srv::Relocalize_Response & msg)
  : msg_(msg)
  {}
  Init_Relocalize_Response_confidence score_normalized(::oomwoo_localization_msgs::srv::Relocalize_Response::_score_normalized_type arg)
  {
    msg_.score_normalized = std::move(arg);
    return Init_Relocalize_Response_confidence(msg_);
  }

private:
  ::oomwoo_localization_msgs::srv::Relocalize_Response msg_;
};

class Init_Relocalize_Response_score
{
public:
  explicit Init_Relocalize_Response_score(::oomwoo_localization_msgs::srv::Relocalize_Response & msg)
  : msg_(msg)
  {}
  Init_Relocalize_Response_score_normalized score(::oomwoo_localization_msgs::srv::Relocalize_Response::_score_type arg)
  {
    msg_.score = std::move(arg);
    return Init_Relocalize_Response_score_normalized(msg_);
  }

private:
  ::oomwoo_localization_msgs::srv::Relocalize_Response msg_;
};

class Init_Relocalize_Response_pose
{
public:
  explicit Init_Relocalize_Response_pose(::oomwoo_localization_msgs::srv::Relocalize_Response & msg)
  : msg_(msg)
  {}
  Init_Relocalize_Response_score pose(::oomwoo_localization_msgs::srv::Relocalize_Response::_pose_type arg)
  {
    msg_.pose = std::move(arg);
    return Init_Relocalize_Response_score(msg_);
  }

private:
  ::oomwoo_localization_msgs::srv::Relocalize_Response msg_;
};

class Init_Relocalize_Response_success
{
public:
  Init_Relocalize_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Relocalize_Response_pose success(::oomwoo_localization_msgs::srv::Relocalize_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_Relocalize_Response_pose(msg_);
  }

private:
  ::oomwoo_localization_msgs::srv::Relocalize_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::oomwoo_localization_msgs::srv::Relocalize_Response>()
{
  return oomwoo_localization_msgs::srv::builder::Init_Relocalize_Response_success();
}

}  // namespace oomwoo_localization_msgs


namespace oomwoo_localization_msgs
{

namespace srv
{

namespace builder
{

class Init_Relocalize_Event_response
{
public:
  explicit Init_Relocalize_Event_response(::oomwoo_localization_msgs::srv::Relocalize_Event & msg)
  : msg_(msg)
  {}
  ::oomwoo_localization_msgs::srv::Relocalize_Event response(::oomwoo_localization_msgs::srv::Relocalize_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::oomwoo_localization_msgs::srv::Relocalize_Event msg_;
};

class Init_Relocalize_Event_request
{
public:
  explicit Init_Relocalize_Event_request(::oomwoo_localization_msgs::srv::Relocalize_Event & msg)
  : msg_(msg)
  {}
  Init_Relocalize_Event_response request(::oomwoo_localization_msgs::srv::Relocalize_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_Relocalize_Event_response(msg_);
  }

private:
  ::oomwoo_localization_msgs::srv::Relocalize_Event msg_;
};

class Init_Relocalize_Event_info
{
public:
  Init_Relocalize_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Relocalize_Event_request info(::oomwoo_localization_msgs::srv::Relocalize_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_Relocalize_Event_request(msg_);
  }

private:
  ::oomwoo_localization_msgs::srv::Relocalize_Event msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::oomwoo_localization_msgs::srv::Relocalize_Event>()
{
  return oomwoo_localization_msgs::srv::builder::Init_Relocalize_Event_info();
}

}  // namespace oomwoo_localization_msgs

#endif  // OOMWOO_LOCALIZATION_MSGS__SRV__DETAIL__RELOCALIZE__BUILDER_HPP_
