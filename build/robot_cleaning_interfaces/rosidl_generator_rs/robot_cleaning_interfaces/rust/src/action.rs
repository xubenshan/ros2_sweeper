
#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



// Corresponds to robot_cleaning_interfaces__action__CleanTask_Goal

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct CleanTask_Goal {

    // This member is not documented.
    #[allow(missing_docs)]
    pub task_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub mode: u8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub regions: Vec<std::string::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub target_coverage: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub resume_checkpoint: bool,

}

impl CleanTask_Goal {

    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ALL: u8 = 0;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const REGIONS: u8 = 1;

}


impl Default for CleanTask_Goal {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::CleanTask_Goal::default())
  }
}

impl rosidl_runtime_rs::Message for CleanTask_Goal {
  type RmwMsg = super::action::rmw::CleanTask_Goal;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        task_id: msg.task_id.as_str().into(),
        mode: msg.mode,
        regions: msg.regions
          .into_iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        target_coverage: msg.target_coverage,
        resume_checkpoint: msg.resume_checkpoint,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        task_id: msg.task_id.as_str().into(),
      mode: msg.mode,
        regions: msg.regions
          .iter()
          .map(|elem| elem.as_str().into())
          .collect(),
      target_coverage: msg.target_coverage,
      resume_checkpoint: msg.resume_checkpoint,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      task_id: msg.task_id.to_string(),
      mode: msg.mode,
      regions: msg.regions
          .into_iter()
          .map(|elem| elem.to_string())
          .collect(),
      target_coverage: msg.target_coverage,
      resume_checkpoint: msg.resume_checkpoint,
    }
  }
}


// Corresponds to robot_cleaning_interfaces__action__CleanTask_Result

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct CleanTask_Result {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub reason: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub coverage: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub path_length_m: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub completed_waypoints: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub failed_waypoints: u32,

}



impl Default for CleanTask_Result {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::CleanTask_Result::default())
  }
}

impl rosidl_runtime_rs::Message for CleanTask_Result {
  type RmwMsg = super::action::rmw::CleanTask_Result;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        success: msg.success,
        reason: msg.reason.as_str().into(),
        coverage: msg.coverage,
        path_length_m: msg.path_length_m,
        completed_waypoints: msg.completed_waypoints,
        failed_waypoints: msg.failed_waypoints,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      success: msg.success,
        reason: msg.reason.as_str().into(),
      coverage: msg.coverage,
      path_length_m: msg.path_length_m,
      completed_waypoints: msg.completed_waypoints,
      failed_waypoints: msg.failed_waypoints,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      success: msg.success,
      reason: msg.reason.to_string(),
      coverage: msg.coverage,
      path_length_m: msg.path_length_m,
      completed_waypoints: msg.completed_waypoints,
      failed_waypoints: msg.failed_waypoints,
    }
  }
}


// Corresponds to robot_cleaning_interfaces__action__CleanTask_Feedback

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct CleanTask_Feedback {

    // This member is not documented.
    #[allow(missing_docs)]
    pub state: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub coverage: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub completed_waypoints: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub total_waypoints: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub current_goal: geometry_msgs::msg::PoseStamped,

}



impl Default for CleanTask_Feedback {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::CleanTask_Feedback::default())
  }
}

impl rosidl_runtime_rs::Message for CleanTask_Feedback {
  type RmwMsg = super::action::rmw::CleanTask_Feedback;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        state: msg.state.as_str().into(),
        coverage: msg.coverage,
        completed_waypoints: msg.completed_waypoints,
        total_waypoints: msg.total_waypoints,
        current_goal: geometry_msgs::msg::PoseStamped::into_rmw_message(std::borrow::Cow::Owned(msg.current_goal)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        state: msg.state.as_str().into(),
      coverage: msg.coverage,
      completed_waypoints: msg.completed_waypoints,
      total_waypoints: msg.total_waypoints,
        current_goal: geometry_msgs::msg::PoseStamped::into_rmw_message(std::borrow::Cow::Borrowed(&msg.current_goal)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      state: msg.state.to_string(),
      coverage: msg.coverage,
      completed_waypoints: msg.completed_waypoints,
      total_waypoints: msg.total_waypoints,
      current_goal: geometry_msgs::msg::PoseStamped::from_rmw_message(msg.current_goal),
    }
  }
}


// Corresponds to robot_cleaning_interfaces__action__CleanTask_FeedbackMessage

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct CleanTask_FeedbackMessage {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::UUID,


    // This member is not documented.
    #[allow(missing_docs)]
    pub feedback: super::action::CleanTask_Feedback,

}



impl Default for CleanTask_FeedbackMessage {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::CleanTask_FeedbackMessage::default())
  }
}

impl rosidl_runtime_rs::Message for CleanTask_FeedbackMessage {
  type RmwMsg = super::action::rmw::CleanTask_FeedbackMessage;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Owned(msg.goal_id)).into_owned(),
        feedback: super::action::CleanTask_Feedback::into_rmw_message(std::borrow::Cow::Owned(msg.feedback)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Borrowed(&msg.goal_id)).into_owned(),
        feedback: super::action::CleanTask_Feedback::into_rmw_message(std::borrow::Cow::Borrowed(&msg.feedback)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      goal_id: unique_identifier_msgs::msg::UUID::from_rmw_message(msg.goal_id),
      feedback: super::action::CleanTask_Feedback::from_rmw_message(msg.feedback),
    }
  }
}






// Corresponds to robot_cleaning_interfaces__action__CleanTask_SendGoal_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct CleanTask_SendGoal_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::UUID,


    // This member is not documented.
    #[allow(missing_docs)]
    pub goal: super::action::CleanTask_Goal,

}



impl Default for CleanTask_SendGoal_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::CleanTask_SendGoal_Request::default())
  }
}

impl rosidl_runtime_rs::Message for CleanTask_SendGoal_Request {
  type RmwMsg = super::action::rmw::CleanTask_SendGoal_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Owned(msg.goal_id)).into_owned(),
        goal: super::action::CleanTask_Goal::into_rmw_message(std::borrow::Cow::Owned(msg.goal)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Borrowed(&msg.goal_id)).into_owned(),
        goal: super::action::CleanTask_Goal::into_rmw_message(std::borrow::Cow::Borrowed(&msg.goal)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      goal_id: unique_identifier_msgs::msg::UUID::from_rmw_message(msg.goal_id),
      goal: super::action::CleanTask_Goal::from_rmw_message(msg.goal),
    }
  }
}


// Corresponds to robot_cleaning_interfaces__action__CleanTask_SendGoal_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct CleanTask_SendGoal_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub accepted: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub stamp: builtin_interfaces::msg::Time,

}



impl Default for CleanTask_SendGoal_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::CleanTask_SendGoal_Response::default())
  }
}

impl rosidl_runtime_rs::Message for CleanTask_SendGoal_Response {
  type RmwMsg = super::action::rmw::CleanTask_SendGoal_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        accepted: msg.accepted,
        stamp: builtin_interfaces::msg::Time::into_rmw_message(std::borrow::Cow::Owned(msg.stamp)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      accepted: msg.accepted,
        stamp: builtin_interfaces::msg::Time::into_rmw_message(std::borrow::Cow::Borrowed(&msg.stamp)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      accepted: msg.accepted,
      stamp: builtin_interfaces::msg::Time::from_rmw_message(msg.stamp),
    }
  }
}


// Corresponds to robot_cleaning_interfaces__action__CleanTask_GetResult_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct CleanTask_GetResult_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::UUID,

}



impl Default for CleanTask_GetResult_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::CleanTask_GetResult_Request::default())
  }
}

impl rosidl_runtime_rs::Message for CleanTask_GetResult_Request {
  type RmwMsg = super::action::rmw::CleanTask_GetResult_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Owned(msg.goal_id)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Borrowed(&msg.goal_id)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      goal_id: unique_identifier_msgs::msg::UUID::from_rmw_message(msg.goal_id),
    }
  }
}


// Corresponds to robot_cleaning_interfaces__action__CleanTask_GetResult_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct CleanTask_GetResult_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub status: i8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub result: super::action::CleanTask_Result,

}



impl Default for CleanTask_GetResult_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::CleanTask_GetResult_Response::default())
  }
}

impl rosidl_runtime_rs::Message for CleanTask_GetResult_Response {
  type RmwMsg = super::action::rmw::CleanTask_GetResult_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        status: msg.status,
        result: super::action::CleanTask_Result::into_rmw_message(std::borrow::Cow::Owned(msg.result)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      status: msg.status,
        result: super::action::CleanTask_Result::into_rmw_message(std::borrow::Cow::Borrowed(&msg.result)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      status: msg.status,
      result: super::action::CleanTask_Result::from_rmw_message(msg.result),
    }
  }
}






#[link(name = "robot_cleaning_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__robot_cleaning_interfaces__action__CleanTask_SendGoal() -> *const std::ffi::c_void;
}

// Corresponds to robot_cleaning_interfaces__action__CleanTask_SendGoal
#[allow(missing_docs, non_camel_case_types)]
pub struct CleanTask_SendGoal;

impl rosidl_runtime_rs::Service for CleanTask_SendGoal {
    type Request = CleanTask_SendGoal_Request;
    type Response = CleanTask_SendGoal_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__robot_cleaning_interfaces__action__CleanTask_SendGoal() }
    }
}




#[link(name = "robot_cleaning_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__robot_cleaning_interfaces__action__CleanTask_GetResult() -> *const std::ffi::c_void;
}

// Corresponds to robot_cleaning_interfaces__action__CleanTask_GetResult
#[allow(missing_docs, non_camel_case_types)]
pub struct CleanTask_GetResult;

impl rosidl_runtime_rs::Service for CleanTask_GetResult {
    type Request = CleanTask_GetResult_Request;
    type Response = CleanTask_GetResult_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__robot_cleaning_interfaces__action__CleanTask_GetResult() }
    }
}






#[link(name = "robot_cleaning_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_action_type_support_handle__robot_cleaning_interfaces__action__CleanTask() -> *const std::ffi::c_void;
}

// Corresponds to robot_cleaning_interfaces__action__CleanTask
#[allow(missing_docs, non_camel_case_types)]
pub struct CleanTask;

impl rosidl_runtime_rs::Action for CleanTask {
  // --- Associated types for client library users ---
  /// The goal message defined in the action definition.
  type Goal = CleanTask_Goal;

  /// The result message defined in the action definition.
  type Result = CleanTask_Result;

  /// The feedback message defined in the action definition.
  type Feedback = CleanTask_Feedback;

  // --- Associated types for client library implementation ---
  /// The feedback message with generic fields which wraps the feedback message.
  type FeedbackMessage = super::action::CleanTask_FeedbackMessage;

  /// The send_goal service using a wrapped version of the goal message as a request.
  type SendGoalService = super::action::CleanTask_SendGoal;

  /// The generic service to cancel a goal.
  type CancelGoalService = action_msgs::srv::rmw::CancelGoal;

  /// The get_result service using a wrapped version of the result message as a response.
  type GetResultService = super::action::CleanTask_GetResult;

  // --- Methods for client library implementation ---
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_action_type_support_handle__robot_cleaning_interfaces__action__CleanTask() }
  }

  fn create_goal_request(
    goal_id: &[u8; 16],
    goal: super::action::rmw::CleanTask_Goal,
  ) -> super::action::rmw::CleanTask_SendGoal_Request {
   super::action::rmw::CleanTask_SendGoal_Request {
      goal_id: unique_identifier_msgs::msg::rmw::UUID { uuid: *goal_id },
      goal,
    }
  }

  fn split_goal_request(
    request: super::action::rmw::CleanTask_SendGoal_Request,
  ) -> (
    [u8; 16],
   super::action::rmw::CleanTask_Goal,
  ) {
    (request.goal_id.uuid, request.goal)
  }

  fn create_goal_response(
    accepted: bool,
    stamp: (i32, u32),
  ) -> super::action::rmw::CleanTask_SendGoal_Response {
   super::action::rmw::CleanTask_SendGoal_Response {
      accepted,
      stamp: builtin_interfaces::msg::rmw::Time {
        sec: stamp.0,
        nanosec: stamp.1,
      },
    }
  }

  fn get_goal_response_accepted(
    response: &super::action::rmw::CleanTask_SendGoal_Response,
  ) -> bool {
    response.accepted
  }

  fn get_goal_response_stamp(
    response: &super::action::rmw::CleanTask_SendGoal_Response,
  ) -> (i32, u32) {
    (response.stamp.sec, response.stamp.nanosec)
  }

  fn create_feedback_message(
    goal_id: &[u8; 16],
    feedback: super::action::rmw::CleanTask_Feedback,
  ) -> super::action::rmw::CleanTask_FeedbackMessage {
    let mut message = super::action::rmw::CleanTask_FeedbackMessage::default();
    message.goal_id.uuid = *goal_id;
    message.feedback = feedback;
    message
  }

  fn split_feedback_message(
    feedback: super::action::rmw::CleanTask_FeedbackMessage,
  ) -> (
    [u8; 16],
   super::action::rmw::CleanTask_Feedback,
  ) {
    (feedback.goal_id.uuid, feedback.feedback)
  }

  fn create_result_request(
    goal_id: &[u8; 16],
  ) -> super::action::rmw::CleanTask_GetResult_Request {
   super::action::rmw::CleanTask_GetResult_Request {
      goal_id: unique_identifier_msgs::msg::rmw::UUID { uuid: *goal_id },
    }
  }

  fn get_result_request_uuid(
    request: &super::action::rmw::CleanTask_GetResult_Request,
  ) -> &[u8; 16] {
    &request.goal_id.uuid
  }

  fn create_result_response(
    status: i8,
    result: super::action::rmw::CleanTask_Result,
  ) -> super::action::rmw::CleanTask_GetResult_Response {
   super::action::rmw::CleanTask_GetResult_Response {
      status,
      result,
    }
  }

  fn split_result_response(
    response: super::action::rmw::CleanTask_GetResult_Response
  ) -> (
    i8,
   super::action::rmw::CleanTask_Result,
  ) {
    (response.status, response.result)
  }
}


