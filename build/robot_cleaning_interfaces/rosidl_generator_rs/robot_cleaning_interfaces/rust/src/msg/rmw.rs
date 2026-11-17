#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};


#[link(name = "robot_cleaning_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__robot_cleaning_interfaces__msg__CleaningEvent() -> *const std::ffi::c_void;
}

#[link(name = "robot_cleaning_interfaces__rosidl_generator_c")]
extern "C" {
    fn robot_cleaning_interfaces__msg__CleaningEvent__init(msg: *mut CleaningEvent) -> bool;
    fn robot_cleaning_interfaces__msg__CleaningEvent__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<CleaningEvent>, size: usize) -> bool;
    fn robot_cleaning_interfaces__msg__CleaningEvent__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<CleaningEvent>);
    fn robot_cleaning_interfaces__msg__CleaningEvent__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<CleaningEvent>, out_seq: *mut rosidl_runtime_rs::Sequence<CleaningEvent>) -> bool;
}

// Corresponds to robot_cleaning_interfaces__msg__CleaningEvent
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct CleaningEvent {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub sequence: u64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub severity: u8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub task_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub code: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub state: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub previous_state: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub recoverable: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub coverage: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub completed_waypoints: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub failed_waypoints: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub total_waypoints: u32,

}

impl CleaningEvent {

    // This constant is not documented.
    #[allow(missing_docs)]
    pub const INFO: u8 = 0;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const WARNING: u8 = 1;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR: u8 = 2;

}


impl Default for CleaningEvent {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !robot_cleaning_interfaces__msg__CleaningEvent__init(&mut msg as *mut _) {
        panic!("Call to robot_cleaning_interfaces__msg__CleaningEvent__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for CleaningEvent {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_cleaning_interfaces__msg__CleaningEvent__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_cleaning_interfaces__msg__CleaningEvent__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_cleaning_interfaces__msg__CleaningEvent__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for CleaningEvent {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for CleaningEvent where Self: Sized {
  const TYPE_NAME: &'static str = "robot_cleaning_interfaces/msg/CleaningEvent";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__robot_cleaning_interfaces__msg__CleaningEvent() }
  }
}


#[link(name = "robot_cleaning_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__robot_cleaning_interfaces__msg__CoverageStatus() -> *const std::ffi::c_void;
}

#[link(name = "robot_cleaning_interfaces__rosidl_generator_c")]
extern "C" {
    fn robot_cleaning_interfaces__msg__CoverageStatus__init(msg: *mut CoverageStatus) -> bool;
    fn robot_cleaning_interfaces__msg__CoverageStatus__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<CoverageStatus>, size: usize) -> bool;
    fn robot_cleaning_interfaces__msg__CoverageStatus__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<CoverageStatus>);
    fn robot_cleaning_interfaces__msg__CoverageStatus__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<CoverageStatus>, out_seq: *mut rosidl_runtime_rs::Sequence<CoverageStatus>) -> bool;
}

// Corresponds to robot_cleaning_interfaces__msg__CoverageStatus
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct CoverageStatus {

    // This member is not documented.
    #[allow(missing_docs)]
    pub task_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub coverage: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub path_length_m: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub covered: nav_msgs::msg::rmw::OccupancyGrid,

}



impl Default for CoverageStatus {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !robot_cleaning_interfaces__msg__CoverageStatus__init(&mut msg as *mut _) {
        panic!("Call to robot_cleaning_interfaces__msg__CoverageStatus__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for CoverageStatus {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_cleaning_interfaces__msg__CoverageStatus__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_cleaning_interfaces__msg__CoverageStatus__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_cleaning_interfaces__msg__CoverageStatus__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for CoverageStatus {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for CoverageStatus where Self: Sized {
  const TYPE_NAME: &'static str = "robot_cleaning_interfaces/msg/CoverageStatus";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__robot_cleaning_interfaces__msg__CoverageStatus() }
  }
}


#[link(name = "robot_cleaning_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__robot_cleaning_interfaces__msg__LocalizationHealth() -> *const std::ffi::c_void;
}

#[link(name = "robot_cleaning_interfaces__rosidl_generator_c")]
extern "C" {
    fn robot_cleaning_interfaces__msg__LocalizationHealth__init(msg: *mut LocalizationHealth) -> bool;
    fn robot_cleaning_interfaces__msg__LocalizationHealth__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<LocalizationHealth>, size: usize) -> bool;
    fn robot_cleaning_interfaces__msg__LocalizationHealth__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<LocalizationHealth>);
    fn robot_cleaning_interfaces__msg__LocalizationHealth__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<LocalizationHealth>, out_seq: *mut rosidl_runtime_rs::Sequence<LocalizationHealth>) -> bool;
}

// Corresponds to robot_cleaning_interfaces__msg__LocalizationHealth
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct LocalizationHealth {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub state: u8,

    /// healthy means motion and coverage accounting may continue. A transient
    /// DEGRADED state remains operational until the configured loss hold expires.
    pub healthy: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub covariance_xy: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub lost_covariance_threshold: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub pose_age_s: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub reason: rosidl_runtime_rs::String,

}

impl LocalizationHealth {

    // This constant is not documented.
    #[allow(missing_docs)]
    pub const UNKNOWN: u8 = 0;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const HEALTHY: u8 = 1;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const DEGRADED: u8 = 2;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const LOST: u8 = 3;

}


impl Default for LocalizationHealth {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !robot_cleaning_interfaces__msg__LocalizationHealth__init(&mut msg as *mut _) {
        panic!("Call to robot_cleaning_interfaces__msg__LocalizationHealth__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for LocalizationHealth {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_cleaning_interfaces__msg__LocalizationHealth__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_cleaning_interfaces__msg__LocalizationHealth__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_cleaning_interfaces__msg__LocalizationHealth__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for LocalizationHealth {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for LocalizationHealth where Self: Sized {
  const TYPE_NAME: &'static str = "robot_cleaning_interfaces/msg/LocalizationHealth";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__robot_cleaning_interfaces__msg__LocalizationHealth() }
  }
}


