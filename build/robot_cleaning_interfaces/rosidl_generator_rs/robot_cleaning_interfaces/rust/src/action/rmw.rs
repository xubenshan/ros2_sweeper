
#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};


#[link(name = "robot_cleaning_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__robot_cleaning_interfaces__action__CleanTask_Goal() -> *const std::ffi::c_void;
}

#[link(name = "robot_cleaning_interfaces__rosidl_generator_c")]
extern "C" {
    fn robot_cleaning_interfaces__action__CleanTask_Goal__init(msg: *mut CleanTask_Goal) -> bool;
    fn robot_cleaning_interfaces__action__CleanTask_Goal__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<CleanTask_Goal>, size: usize) -> bool;
    fn robot_cleaning_interfaces__action__CleanTask_Goal__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<CleanTask_Goal>);
    fn robot_cleaning_interfaces__action__CleanTask_Goal__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<CleanTask_Goal>, out_seq: *mut rosidl_runtime_rs::Sequence<CleanTask_Goal>) -> bool;
}

// Corresponds to robot_cleaning_interfaces__action__CleanTask_Goal
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct CleanTask_Goal {

    // This member is not documented.
    #[allow(missing_docs)]
    pub task_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub mode: u8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub regions: rosidl_runtime_rs::Sequence<rosidl_runtime_rs::String>,


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
    unsafe {
      let mut msg = std::mem::zeroed();
      if !robot_cleaning_interfaces__action__CleanTask_Goal__init(&mut msg as *mut _) {
        panic!("Call to robot_cleaning_interfaces__action__CleanTask_Goal__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for CleanTask_Goal {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_cleaning_interfaces__action__CleanTask_Goal__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_cleaning_interfaces__action__CleanTask_Goal__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_cleaning_interfaces__action__CleanTask_Goal__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for CleanTask_Goal {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for CleanTask_Goal where Self: Sized {
  const TYPE_NAME: &'static str = "robot_cleaning_interfaces/action/CleanTask_Goal";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__robot_cleaning_interfaces__action__CleanTask_Goal() }
  }
}


#[link(name = "robot_cleaning_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__robot_cleaning_interfaces__action__CleanTask_Result() -> *const std::ffi::c_void;
}

#[link(name = "robot_cleaning_interfaces__rosidl_generator_c")]
extern "C" {
    fn robot_cleaning_interfaces__action__CleanTask_Result__init(msg: *mut CleanTask_Result) -> bool;
    fn robot_cleaning_interfaces__action__CleanTask_Result__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<CleanTask_Result>, size: usize) -> bool;
    fn robot_cleaning_interfaces__action__CleanTask_Result__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<CleanTask_Result>);
    fn robot_cleaning_interfaces__action__CleanTask_Result__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<CleanTask_Result>, out_seq: *mut rosidl_runtime_rs::Sequence<CleanTask_Result>) -> bool;
}

// Corresponds to robot_cleaning_interfaces__action__CleanTask_Result
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct CleanTask_Result {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub reason: rosidl_runtime_rs::String,


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
    unsafe {
      let mut msg = std::mem::zeroed();
      if !robot_cleaning_interfaces__action__CleanTask_Result__init(&mut msg as *mut _) {
        panic!("Call to robot_cleaning_interfaces__action__CleanTask_Result__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for CleanTask_Result {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_cleaning_interfaces__action__CleanTask_Result__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_cleaning_interfaces__action__CleanTask_Result__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_cleaning_interfaces__action__CleanTask_Result__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for CleanTask_Result {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for CleanTask_Result where Self: Sized {
  const TYPE_NAME: &'static str = "robot_cleaning_interfaces/action/CleanTask_Result";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__robot_cleaning_interfaces__action__CleanTask_Result() }
  }
}


#[link(name = "robot_cleaning_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__robot_cleaning_interfaces__action__CleanTask_Feedback() -> *const std::ffi::c_void;
}

#[link(name = "robot_cleaning_interfaces__rosidl_generator_c")]
extern "C" {
    fn robot_cleaning_interfaces__action__CleanTask_Feedback__init(msg: *mut CleanTask_Feedback) -> bool;
    fn robot_cleaning_interfaces__action__CleanTask_Feedback__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<CleanTask_Feedback>, size: usize) -> bool;
    fn robot_cleaning_interfaces__action__CleanTask_Feedback__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<CleanTask_Feedback>);
    fn robot_cleaning_interfaces__action__CleanTask_Feedback__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<CleanTask_Feedback>, out_seq: *mut rosidl_runtime_rs::Sequence<CleanTask_Feedback>) -> bool;
}

// Corresponds to robot_cleaning_interfaces__action__CleanTask_Feedback
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct CleanTask_Feedback {

    // This member is not documented.
    #[allow(missing_docs)]
    pub state: rosidl_runtime_rs::String,


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
    pub current_goal: geometry_msgs::msg::rmw::PoseStamped,

}



impl Default for CleanTask_Feedback {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !robot_cleaning_interfaces__action__CleanTask_Feedback__init(&mut msg as *mut _) {
        panic!("Call to robot_cleaning_interfaces__action__CleanTask_Feedback__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for CleanTask_Feedback {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_cleaning_interfaces__action__CleanTask_Feedback__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_cleaning_interfaces__action__CleanTask_Feedback__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_cleaning_interfaces__action__CleanTask_Feedback__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for CleanTask_Feedback {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for CleanTask_Feedback where Self: Sized {
  const TYPE_NAME: &'static str = "robot_cleaning_interfaces/action/CleanTask_Feedback";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__robot_cleaning_interfaces__action__CleanTask_Feedback() }
  }
}


#[link(name = "robot_cleaning_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__robot_cleaning_interfaces__action__CleanTask_FeedbackMessage() -> *const std::ffi::c_void;
}

#[link(name = "robot_cleaning_interfaces__rosidl_generator_c")]
extern "C" {
    fn robot_cleaning_interfaces__action__CleanTask_FeedbackMessage__init(msg: *mut CleanTask_FeedbackMessage) -> bool;
    fn robot_cleaning_interfaces__action__CleanTask_FeedbackMessage__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<CleanTask_FeedbackMessage>, size: usize) -> bool;
    fn robot_cleaning_interfaces__action__CleanTask_FeedbackMessage__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<CleanTask_FeedbackMessage>);
    fn robot_cleaning_interfaces__action__CleanTask_FeedbackMessage__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<CleanTask_FeedbackMessage>, out_seq: *mut rosidl_runtime_rs::Sequence<CleanTask_FeedbackMessage>) -> bool;
}

// Corresponds to robot_cleaning_interfaces__action__CleanTask_FeedbackMessage
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct CleanTask_FeedbackMessage {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::rmw::UUID,


    // This member is not documented.
    #[allow(missing_docs)]
    pub feedback: super::super::action::rmw::CleanTask_Feedback,

}



impl Default for CleanTask_FeedbackMessage {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !robot_cleaning_interfaces__action__CleanTask_FeedbackMessage__init(&mut msg as *mut _) {
        panic!("Call to robot_cleaning_interfaces__action__CleanTask_FeedbackMessage__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for CleanTask_FeedbackMessage {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_cleaning_interfaces__action__CleanTask_FeedbackMessage__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_cleaning_interfaces__action__CleanTask_FeedbackMessage__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_cleaning_interfaces__action__CleanTask_FeedbackMessage__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for CleanTask_FeedbackMessage {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for CleanTask_FeedbackMessage where Self: Sized {
  const TYPE_NAME: &'static str = "robot_cleaning_interfaces/action/CleanTask_FeedbackMessage";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__robot_cleaning_interfaces__action__CleanTask_FeedbackMessage() }
  }
}




#[link(name = "robot_cleaning_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__robot_cleaning_interfaces__action__CleanTask_SendGoal_Request() -> *const std::ffi::c_void;
}

#[link(name = "robot_cleaning_interfaces__rosidl_generator_c")]
extern "C" {
    fn robot_cleaning_interfaces__action__CleanTask_SendGoal_Request__init(msg: *mut CleanTask_SendGoal_Request) -> bool;
    fn robot_cleaning_interfaces__action__CleanTask_SendGoal_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<CleanTask_SendGoal_Request>, size: usize) -> bool;
    fn robot_cleaning_interfaces__action__CleanTask_SendGoal_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<CleanTask_SendGoal_Request>);
    fn robot_cleaning_interfaces__action__CleanTask_SendGoal_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<CleanTask_SendGoal_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<CleanTask_SendGoal_Request>) -> bool;
}

// Corresponds to robot_cleaning_interfaces__action__CleanTask_SendGoal_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct CleanTask_SendGoal_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::rmw::UUID,


    // This member is not documented.
    #[allow(missing_docs)]
    pub goal: super::super::action::rmw::CleanTask_Goal,

}



impl Default for CleanTask_SendGoal_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !robot_cleaning_interfaces__action__CleanTask_SendGoal_Request__init(&mut msg as *mut _) {
        panic!("Call to robot_cleaning_interfaces__action__CleanTask_SendGoal_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for CleanTask_SendGoal_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_cleaning_interfaces__action__CleanTask_SendGoal_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_cleaning_interfaces__action__CleanTask_SendGoal_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_cleaning_interfaces__action__CleanTask_SendGoal_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for CleanTask_SendGoal_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for CleanTask_SendGoal_Request where Self: Sized {
  const TYPE_NAME: &'static str = "robot_cleaning_interfaces/action/CleanTask_SendGoal_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__robot_cleaning_interfaces__action__CleanTask_SendGoal_Request() }
  }
}


#[link(name = "robot_cleaning_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__robot_cleaning_interfaces__action__CleanTask_SendGoal_Response() -> *const std::ffi::c_void;
}

#[link(name = "robot_cleaning_interfaces__rosidl_generator_c")]
extern "C" {
    fn robot_cleaning_interfaces__action__CleanTask_SendGoal_Response__init(msg: *mut CleanTask_SendGoal_Response) -> bool;
    fn robot_cleaning_interfaces__action__CleanTask_SendGoal_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<CleanTask_SendGoal_Response>, size: usize) -> bool;
    fn robot_cleaning_interfaces__action__CleanTask_SendGoal_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<CleanTask_SendGoal_Response>);
    fn robot_cleaning_interfaces__action__CleanTask_SendGoal_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<CleanTask_SendGoal_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<CleanTask_SendGoal_Response>) -> bool;
}

// Corresponds to robot_cleaning_interfaces__action__CleanTask_SendGoal_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct CleanTask_SendGoal_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub accepted: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub stamp: builtin_interfaces::msg::rmw::Time,

}



impl Default for CleanTask_SendGoal_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !robot_cleaning_interfaces__action__CleanTask_SendGoal_Response__init(&mut msg as *mut _) {
        panic!("Call to robot_cleaning_interfaces__action__CleanTask_SendGoal_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for CleanTask_SendGoal_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_cleaning_interfaces__action__CleanTask_SendGoal_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_cleaning_interfaces__action__CleanTask_SendGoal_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_cleaning_interfaces__action__CleanTask_SendGoal_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for CleanTask_SendGoal_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for CleanTask_SendGoal_Response where Self: Sized {
  const TYPE_NAME: &'static str = "robot_cleaning_interfaces/action/CleanTask_SendGoal_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__robot_cleaning_interfaces__action__CleanTask_SendGoal_Response() }
  }
}


#[link(name = "robot_cleaning_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__robot_cleaning_interfaces__action__CleanTask_GetResult_Request() -> *const std::ffi::c_void;
}

#[link(name = "robot_cleaning_interfaces__rosidl_generator_c")]
extern "C" {
    fn robot_cleaning_interfaces__action__CleanTask_GetResult_Request__init(msg: *mut CleanTask_GetResult_Request) -> bool;
    fn robot_cleaning_interfaces__action__CleanTask_GetResult_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<CleanTask_GetResult_Request>, size: usize) -> bool;
    fn robot_cleaning_interfaces__action__CleanTask_GetResult_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<CleanTask_GetResult_Request>);
    fn robot_cleaning_interfaces__action__CleanTask_GetResult_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<CleanTask_GetResult_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<CleanTask_GetResult_Request>) -> bool;
}

// Corresponds to robot_cleaning_interfaces__action__CleanTask_GetResult_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct CleanTask_GetResult_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::rmw::UUID,

}



impl Default for CleanTask_GetResult_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !robot_cleaning_interfaces__action__CleanTask_GetResult_Request__init(&mut msg as *mut _) {
        panic!("Call to robot_cleaning_interfaces__action__CleanTask_GetResult_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for CleanTask_GetResult_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_cleaning_interfaces__action__CleanTask_GetResult_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_cleaning_interfaces__action__CleanTask_GetResult_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_cleaning_interfaces__action__CleanTask_GetResult_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for CleanTask_GetResult_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for CleanTask_GetResult_Request where Self: Sized {
  const TYPE_NAME: &'static str = "robot_cleaning_interfaces/action/CleanTask_GetResult_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__robot_cleaning_interfaces__action__CleanTask_GetResult_Request() }
  }
}


#[link(name = "robot_cleaning_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__robot_cleaning_interfaces__action__CleanTask_GetResult_Response() -> *const std::ffi::c_void;
}

#[link(name = "robot_cleaning_interfaces__rosidl_generator_c")]
extern "C" {
    fn robot_cleaning_interfaces__action__CleanTask_GetResult_Response__init(msg: *mut CleanTask_GetResult_Response) -> bool;
    fn robot_cleaning_interfaces__action__CleanTask_GetResult_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<CleanTask_GetResult_Response>, size: usize) -> bool;
    fn robot_cleaning_interfaces__action__CleanTask_GetResult_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<CleanTask_GetResult_Response>);
    fn robot_cleaning_interfaces__action__CleanTask_GetResult_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<CleanTask_GetResult_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<CleanTask_GetResult_Response>) -> bool;
}

// Corresponds to robot_cleaning_interfaces__action__CleanTask_GetResult_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct CleanTask_GetResult_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub status: i8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub result: super::super::action::rmw::CleanTask_Result,

}



impl Default for CleanTask_GetResult_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !robot_cleaning_interfaces__action__CleanTask_GetResult_Response__init(&mut msg as *mut _) {
        panic!("Call to robot_cleaning_interfaces__action__CleanTask_GetResult_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for CleanTask_GetResult_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_cleaning_interfaces__action__CleanTask_GetResult_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_cleaning_interfaces__action__CleanTask_GetResult_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_cleaning_interfaces__action__CleanTask_GetResult_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for CleanTask_GetResult_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for CleanTask_GetResult_Response where Self: Sized {
  const TYPE_NAME: &'static str = "robot_cleaning_interfaces/action/CleanTask_GetResult_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__robot_cleaning_interfaces__action__CleanTask_GetResult_Response() }
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


