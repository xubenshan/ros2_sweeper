// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from robot_cleaning_interfaces:action/CleanTask.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "robot_cleaning_interfaces/action/clean_task.hpp"


#ifndef ROBOT_CLEANING_INTERFACES__ACTION__DETAIL__CLEAN_TASK__BUILDER_HPP_
#define ROBOT_CLEANING_INTERFACES__ACTION__DETAIL__CLEAN_TASK__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "robot_cleaning_interfaces/action/detail/clean_task__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace robot_cleaning_interfaces
{

namespace action
{

namespace builder
{

class Init_CleanTask_Goal_resume_checkpoint
{
public:
  explicit Init_CleanTask_Goal_resume_checkpoint(::robot_cleaning_interfaces::action::CleanTask_Goal & msg)
  : msg_(msg)
  {}
  ::robot_cleaning_interfaces::action::CleanTask_Goal resume_checkpoint(::robot_cleaning_interfaces::action::CleanTask_Goal::_resume_checkpoint_type arg)
  {
    msg_.resume_checkpoint = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_cleaning_interfaces::action::CleanTask_Goal msg_;
};

class Init_CleanTask_Goal_target_coverage
{
public:
  explicit Init_CleanTask_Goal_target_coverage(::robot_cleaning_interfaces::action::CleanTask_Goal & msg)
  : msg_(msg)
  {}
  Init_CleanTask_Goal_resume_checkpoint target_coverage(::robot_cleaning_interfaces::action::CleanTask_Goal::_target_coverage_type arg)
  {
    msg_.target_coverage = std::move(arg);
    return Init_CleanTask_Goal_resume_checkpoint(msg_);
  }

private:
  ::robot_cleaning_interfaces::action::CleanTask_Goal msg_;
};

class Init_CleanTask_Goal_regions
{
public:
  explicit Init_CleanTask_Goal_regions(::robot_cleaning_interfaces::action::CleanTask_Goal & msg)
  : msg_(msg)
  {}
  Init_CleanTask_Goal_target_coverage regions(::robot_cleaning_interfaces::action::CleanTask_Goal::_regions_type arg)
  {
    msg_.regions = std::move(arg);
    return Init_CleanTask_Goal_target_coverage(msg_);
  }

private:
  ::robot_cleaning_interfaces::action::CleanTask_Goal msg_;
};

class Init_CleanTask_Goal_mode
{
public:
  explicit Init_CleanTask_Goal_mode(::robot_cleaning_interfaces::action::CleanTask_Goal & msg)
  : msg_(msg)
  {}
  Init_CleanTask_Goal_regions mode(::robot_cleaning_interfaces::action::CleanTask_Goal::_mode_type arg)
  {
    msg_.mode = std::move(arg);
    return Init_CleanTask_Goal_regions(msg_);
  }

private:
  ::robot_cleaning_interfaces::action::CleanTask_Goal msg_;
};

class Init_CleanTask_Goal_task_id
{
public:
  Init_CleanTask_Goal_task_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_CleanTask_Goal_mode task_id(::robot_cleaning_interfaces::action::CleanTask_Goal::_task_id_type arg)
  {
    msg_.task_id = std::move(arg);
    return Init_CleanTask_Goal_mode(msg_);
  }

private:
  ::robot_cleaning_interfaces::action::CleanTask_Goal msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_cleaning_interfaces::action::CleanTask_Goal>()
{
  return robot_cleaning_interfaces::action::builder::Init_CleanTask_Goal_task_id();
}

}  // namespace robot_cleaning_interfaces


namespace robot_cleaning_interfaces
{

namespace action
{

namespace builder
{

class Init_CleanTask_Result_failed_waypoints
{
public:
  explicit Init_CleanTask_Result_failed_waypoints(::robot_cleaning_interfaces::action::CleanTask_Result & msg)
  : msg_(msg)
  {}
  ::robot_cleaning_interfaces::action::CleanTask_Result failed_waypoints(::robot_cleaning_interfaces::action::CleanTask_Result::_failed_waypoints_type arg)
  {
    msg_.failed_waypoints = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_cleaning_interfaces::action::CleanTask_Result msg_;
};

class Init_CleanTask_Result_completed_waypoints
{
public:
  explicit Init_CleanTask_Result_completed_waypoints(::robot_cleaning_interfaces::action::CleanTask_Result & msg)
  : msg_(msg)
  {}
  Init_CleanTask_Result_failed_waypoints completed_waypoints(::robot_cleaning_interfaces::action::CleanTask_Result::_completed_waypoints_type arg)
  {
    msg_.completed_waypoints = std::move(arg);
    return Init_CleanTask_Result_failed_waypoints(msg_);
  }

private:
  ::robot_cleaning_interfaces::action::CleanTask_Result msg_;
};

class Init_CleanTask_Result_path_length_m
{
public:
  explicit Init_CleanTask_Result_path_length_m(::robot_cleaning_interfaces::action::CleanTask_Result & msg)
  : msg_(msg)
  {}
  Init_CleanTask_Result_completed_waypoints path_length_m(::robot_cleaning_interfaces::action::CleanTask_Result::_path_length_m_type arg)
  {
    msg_.path_length_m = std::move(arg);
    return Init_CleanTask_Result_completed_waypoints(msg_);
  }

private:
  ::robot_cleaning_interfaces::action::CleanTask_Result msg_;
};

class Init_CleanTask_Result_coverage
{
public:
  explicit Init_CleanTask_Result_coverage(::robot_cleaning_interfaces::action::CleanTask_Result & msg)
  : msg_(msg)
  {}
  Init_CleanTask_Result_path_length_m coverage(::robot_cleaning_interfaces::action::CleanTask_Result::_coverage_type arg)
  {
    msg_.coverage = std::move(arg);
    return Init_CleanTask_Result_path_length_m(msg_);
  }

private:
  ::robot_cleaning_interfaces::action::CleanTask_Result msg_;
};

class Init_CleanTask_Result_reason
{
public:
  explicit Init_CleanTask_Result_reason(::robot_cleaning_interfaces::action::CleanTask_Result & msg)
  : msg_(msg)
  {}
  Init_CleanTask_Result_coverage reason(::robot_cleaning_interfaces::action::CleanTask_Result::_reason_type arg)
  {
    msg_.reason = std::move(arg);
    return Init_CleanTask_Result_coverage(msg_);
  }

private:
  ::robot_cleaning_interfaces::action::CleanTask_Result msg_;
};

class Init_CleanTask_Result_success
{
public:
  Init_CleanTask_Result_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_CleanTask_Result_reason success(::robot_cleaning_interfaces::action::CleanTask_Result::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_CleanTask_Result_reason(msg_);
  }

private:
  ::robot_cleaning_interfaces::action::CleanTask_Result msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_cleaning_interfaces::action::CleanTask_Result>()
{
  return robot_cleaning_interfaces::action::builder::Init_CleanTask_Result_success();
}

}  // namespace robot_cleaning_interfaces


namespace robot_cleaning_interfaces
{

namespace action
{

namespace builder
{

class Init_CleanTask_Feedback_current_goal
{
public:
  explicit Init_CleanTask_Feedback_current_goal(::robot_cleaning_interfaces::action::CleanTask_Feedback & msg)
  : msg_(msg)
  {}
  ::robot_cleaning_interfaces::action::CleanTask_Feedback current_goal(::robot_cleaning_interfaces::action::CleanTask_Feedback::_current_goal_type arg)
  {
    msg_.current_goal = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_cleaning_interfaces::action::CleanTask_Feedback msg_;
};

class Init_CleanTask_Feedback_total_waypoints
{
public:
  explicit Init_CleanTask_Feedback_total_waypoints(::robot_cleaning_interfaces::action::CleanTask_Feedback & msg)
  : msg_(msg)
  {}
  Init_CleanTask_Feedback_current_goal total_waypoints(::robot_cleaning_interfaces::action::CleanTask_Feedback::_total_waypoints_type arg)
  {
    msg_.total_waypoints = std::move(arg);
    return Init_CleanTask_Feedback_current_goal(msg_);
  }

private:
  ::robot_cleaning_interfaces::action::CleanTask_Feedback msg_;
};

class Init_CleanTask_Feedback_completed_waypoints
{
public:
  explicit Init_CleanTask_Feedback_completed_waypoints(::robot_cleaning_interfaces::action::CleanTask_Feedback & msg)
  : msg_(msg)
  {}
  Init_CleanTask_Feedback_total_waypoints completed_waypoints(::robot_cleaning_interfaces::action::CleanTask_Feedback::_completed_waypoints_type arg)
  {
    msg_.completed_waypoints = std::move(arg);
    return Init_CleanTask_Feedback_total_waypoints(msg_);
  }

private:
  ::robot_cleaning_interfaces::action::CleanTask_Feedback msg_;
};

class Init_CleanTask_Feedback_coverage
{
public:
  explicit Init_CleanTask_Feedback_coverage(::robot_cleaning_interfaces::action::CleanTask_Feedback & msg)
  : msg_(msg)
  {}
  Init_CleanTask_Feedback_completed_waypoints coverage(::robot_cleaning_interfaces::action::CleanTask_Feedback::_coverage_type arg)
  {
    msg_.coverage = std::move(arg);
    return Init_CleanTask_Feedback_completed_waypoints(msg_);
  }

private:
  ::robot_cleaning_interfaces::action::CleanTask_Feedback msg_;
};

class Init_CleanTask_Feedback_state
{
public:
  Init_CleanTask_Feedback_state()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_CleanTask_Feedback_coverage state(::robot_cleaning_interfaces::action::CleanTask_Feedback::_state_type arg)
  {
    msg_.state = std::move(arg);
    return Init_CleanTask_Feedback_coverage(msg_);
  }

private:
  ::robot_cleaning_interfaces::action::CleanTask_Feedback msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_cleaning_interfaces::action::CleanTask_Feedback>()
{
  return robot_cleaning_interfaces::action::builder::Init_CleanTask_Feedback_state();
}

}  // namespace robot_cleaning_interfaces


namespace robot_cleaning_interfaces
{

namespace action
{

namespace builder
{

class Init_CleanTask_SendGoal_Request_goal
{
public:
  explicit Init_CleanTask_SendGoal_Request_goal(::robot_cleaning_interfaces::action::CleanTask_SendGoal_Request & msg)
  : msg_(msg)
  {}
  ::robot_cleaning_interfaces::action::CleanTask_SendGoal_Request goal(::robot_cleaning_interfaces::action::CleanTask_SendGoal_Request::_goal_type arg)
  {
    msg_.goal = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_cleaning_interfaces::action::CleanTask_SendGoal_Request msg_;
};

class Init_CleanTask_SendGoal_Request_goal_id
{
public:
  Init_CleanTask_SendGoal_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_CleanTask_SendGoal_Request_goal goal_id(::robot_cleaning_interfaces::action::CleanTask_SendGoal_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_CleanTask_SendGoal_Request_goal(msg_);
  }

private:
  ::robot_cleaning_interfaces::action::CleanTask_SendGoal_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_cleaning_interfaces::action::CleanTask_SendGoal_Request>()
{
  return robot_cleaning_interfaces::action::builder::Init_CleanTask_SendGoal_Request_goal_id();
}

}  // namespace robot_cleaning_interfaces


namespace robot_cleaning_interfaces
{

namespace action
{

namespace builder
{

class Init_CleanTask_SendGoal_Response_stamp
{
public:
  explicit Init_CleanTask_SendGoal_Response_stamp(::robot_cleaning_interfaces::action::CleanTask_SendGoal_Response & msg)
  : msg_(msg)
  {}
  ::robot_cleaning_interfaces::action::CleanTask_SendGoal_Response stamp(::robot_cleaning_interfaces::action::CleanTask_SendGoal_Response::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_cleaning_interfaces::action::CleanTask_SendGoal_Response msg_;
};

class Init_CleanTask_SendGoal_Response_accepted
{
public:
  Init_CleanTask_SendGoal_Response_accepted()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_CleanTask_SendGoal_Response_stamp accepted(::robot_cleaning_interfaces::action::CleanTask_SendGoal_Response::_accepted_type arg)
  {
    msg_.accepted = std::move(arg);
    return Init_CleanTask_SendGoal_Response_stamp(msg_);
  }

private:
  ::robot_cleaning_interfaces::action::CleanTask_SendGoal_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_cleaning_interfaces::action::CleanTask_SendGoal_Response>()
{
  return robot_cleaning_interfaces::action::builder::Init_CleanTask_SendGoal_Response_accepted();
}

}  // namespace robot_cleaning_interfaces


namespace robot_cleaning_interfaces
{

namespace action
{

namespace builder
{

class Init_CleanTask_SendGoal_Event_response
{
public:
  explicit Init_CleanTask_SendGoal_Event_response(::robot_cleaning_interfaces::action::CleanTask_SendGoal_Event & msg)
  : msg_(msg)
  {}
  ::robot_cleaning_interfaces::action::CleanTask_SendGoal_Event response(::robot_cleaning_interfaces::action::CleanTask_SendGoal_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_cleaning_interfaces::action::CleanTask_SendGoal_Event msg_;
};

class Init_CleanTask_SendGoal_Event_request
{
public:
  explicit Init_CleanTask_SendGoal_Event_request(::robot_cleaning_interfaces::action::CleanTask_SendGoal_Event & msg)
  : msg_(msg)
  {}
  Init_CleanTask_SendGoal_Event_response request(::robot_cleaning_interfaces::action::CleanTask_SendGoal_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_CleanTask_SendGoal_Event_response(msg_);
  }

private:
  ::robot_cleaning_interfaces::action::CleanTask_SendGoal_Event msg_;
};

class Init_CleanTask_SendGoal_Event_info
{
public:
  Init_CleanTask_SendGoal_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_CleanTask_SendGoal_Event_request info(::robot_cleaning_interfaces::action::CleanTask_SendGoal_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_CleanTask_SendGoal_Event_request(msg_);
  }

private:
  ::robot_cleaning_interfaces::action::CleanTask_SendGoal_Event msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_cleaning_interfaces::action::CleanTask_SendGoal_Event>()
{
  return robot_cleaning_interfaces::action::builder::Init_CleanTask_SendGoal_Event_info();
}

}  // namespace robot_cleaning_interfaces


namespace robot_cleaning_interfaces
{

namespace action
{

namespace builder
{

class Init_CleanTask_GetResult_Request_goal_id
{
public:
  Init_CleanTask_GetResult_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::robot_cleaning_interfaces::action::CleanTask_GetResult_Request goal_id(::robot_cleaning_interfaces::action::CleanTask_GetResult_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_cleaning_interfaces::action::CleanTask_GetResult_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_cleaning_interfaces::action::CleanTask_GetResult_Request>()
{
  return robot_cleaning_interfaces::action::builder::Init_CleanTask_GetResult_Request_goal_id();
}

}  // namespace robot_cleaning_interfaces


namespace robot_cleaning_interfaces
{

namespace action
{

namespace builder
{

class Init_CleanTask_GetResult_Response_result
{
public:
  explicit Init_CleanTask_GetResult_Response_result(::robot_cleaning_interfaces::action::CleanTask_GetResult_Response & msg)
  : msg_(msg)
  {}
  ::robot_cleaning_interfaces::action::CleanTask_GetResult_Response result(::robot_cleaning_interfaces::action::CleanTask_GetResult_Response::_result_type arg)
  {
    msg_.result = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_cleaning_interfaces::action::CleanTask_GetResult_Response msg_;
};

class Init_CleanTask_GetResult_Response_status
{
public:
  Init_CleanTask_GetResult_Response_status()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_CleanTask_GetResult_Response_result status(::robot_cleaning_interfaces::action::CleanTask_GetResult_Response::_status_type arg)
  {
    msg_.status = std::move(arg);
    return Init_CleanTask_GetResult_Response_result(msg_);
  }

private:
  ::robot_cleaning_interfaces::action::CleanTask_GetResult_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_cleaning_interfaces::action::CleanTask_GetResult_Response>()
{
  return robot_cleaning_interfaces::action::builder::Init_CleanTask_GetResult_Response_status();
}

}  // namespace robot_cleaning_interfaces


namespace robot_cleaning_interfaces
{

namespace action
{

namespace builder
{

class Init_CleanTask_GetResult_Event_response
{
public:
  explicit Init_CleanTask_GetResult_Event_response(::robot_cleaning_interfaces::action::CleanTask_GetResult_Event & msg)
  : msg_(msg)
  {}
  ::robot_cleaning_interfaces::action::CleanTask_GetResult_Event response(::robot_cleaning_interfaces::action::CleanTask_GetResult_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_cleaning_interfaces::action::CleanTask_GetResult_Event msg_;
};

class Init_CleanTask_GetResult_Event_request
{
public:
  explicit Init_CleanTask_GetResult_Event_request(::robot_cleaning_interfaces::action::CleanTask_GetResult_Event & msg)
  : msg_(msg)
  {}
  Init_CleanTask_GetResult_Event_response request(::robot_cleaning_interfaces::action::CleanTask_GetResult_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_CleanTask_GetResult_Event_response(msg_);
  }

private:
  ::robot_cleaning_interfaces::action::CleanTask_GetResult_Event msg_;
};

class Init_CleanTask_GetResult_Event_info
{
public:
  Init_CleanTask_GetResult_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_CleanTask_GetResult_Event_request info(::robot_cleaning_interfaces::action::CleanTask_GetResult_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_CleanTask_GetResult_Event_request(msg_);
  }

private:
  ::robot_cleaning_interfaces::action::CleanTask_GetResult_Event msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_cleaning_interfaces::action::CleanTask_GetResult_Event>()
{
  return robot_cleaning_interfaces::action::builder::Init_CleanTask_GetResult_Event_info();
}

}  // namespace robot_cleaning_interfaces


namespace robot_cleaning_interfaces
{

namespace action
{

namespace builder
{

class Init_CleanTask_FeedbackMessage_feedback
{
public:
  explicit Init_CleanTask_FeedbackMessage_feedback(::robot_cleaning_interfaces::action::CleanTask_FeedbackMessage & msg)
  : msg_(msg)
  {}
  ::robot_cleaning_interfaces::action::CleanTask_FeedbackMessage feedback(::robot_cleaning_interfaces::action::CleanTask_FeedbackMessage::_feedback_type arg)
  {
    msg_.feedback = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_cleaning_interfaces::action::CleanTask_FeedbackMessage msg_;
};

class Init_CleanTask_FeedbackMessage_goal_id
{
public:
  Init_CleanTask_FeedbackMessage_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_CleanTask_FeedbackMessage_feedback goal_id(::robot_cleaning_interfaces::action::CleanTask_FeedbackMessage::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_CleanTask_FeedbackMessage_feedback(msg_);
  }

private:
  ::robot_cleaning_interfaces::action::CleanTask_FeedbackMessage msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_cleaning_interfaces::action::CleanTask_FeedbackMessage>()
{
  return robot_cleaning_interfaces::action::builder::Init_CleanTask_FeedbackMessage_goal_id();
}

}  // namespace robot_cleaning_interfaces

#endif  // ROBOT_CLEANING_INTERFACES__ACTION__DETAIL__CLEAN_TASK__BUILDER_HPP_
