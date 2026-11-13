#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



#[link(name = "robot_cleaning_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__robot_cleaning_interfaces__srv__BeginCoverage_Request() -> *const std::ffi::c_void;
}

#[link(name = "robot_cleaning_interfaces__rosidl_generator_c")]
extern "C" {
    fn robot_cleaning_interfaces__srv__BeginCoverage_Request__init(msg: *mut BeginCoverage_Request) -> bool;
    fn robot_cleaning_interfaces__srv__BeginCoverage_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<BeginCoverage_Request>, size: usize) -> bool;
    fn robot_cleaning_interfaces__srv__BeginCoverage_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<BeginCoverage_Request>);
    fn robot_cleaning_interfaces__srv__BeginCoverage_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<BeginCoverage_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<BeginCoverage_Request>) -> bool;
}

// Corresponds to robot_cleaning_interfaces__srv__BeginCoverage_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct BeginCoverage_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub task_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub regions: rosidl_runtime_rs::Sequence<rosidl_runtime_rs::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub start: geometry_msgs::msg::rmw::PoseStamped,


    // This member is not documented.
    #[allow(missing_docs)]
    pub restored_grid: rosidl_runtime_rs::Sequence<i8>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub restored_distance_m: f64,

}



impl Default for BeginCoverage_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !robot_cleaning_interfaces__srv__BeginCoverage_Request__init(&mut msg as *mut _) {
        panic!("Call to robot_cleaning_interfaces__srv__BeginCoverage_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for BeginCoverage_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_cleaning_interfaces__srv__BeginCoverage_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_cleaning_interfaces__srv__BeginCoverage_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_cleaning_interfaces__srv__BeginCoverage_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for BeginCoverage_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for BeginCoverage_Request where Self: Sized {
  const TYPE_NAME: &'static str = "robot_cleaning_interfaces/srv/BeginCoverage_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__robot_cleaning_interfaces__srv__BeginCoverage_Request() }
  }
}


#[link(name = "robot_cleaning_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__robot_cleaning_interfaces__srv__BeginCoverage_Response() -> *const std::ffi::c_void;
}

#[link(name = "robot_cleaning_interfaces__rosidl_generator_c")]
extern "C" {
    fn robot_cleaning_interfaces__srv__BeginCoverage_Response__init(msg: *mut BeginCoverage_Response) -> bool;
    fn robot_cleaning_interfaces__srv__BeginCoverage_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<BeginCoverage_Response>, size: usize) -> bool;
    fn robot_cleaning_interfaces__srv__BeginCoverage_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<BeginCoverage_Response>);
    fn robot_cleaning_interfaces__srv__BeginCoverage_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<BeginCoverage_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<BeginCoverage_Response>) -> bool;
}

// Corresponds to robot_cleaning_interfaces__srv__BeginCoverage_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct BeginCoverage_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub reason: rosidl_runtime_rs::String,

}



impl Default for BeginCoverage_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !robot_cleaning_interfaces__srv__BeginCoverage_Response__init(&mut msg as *mut _) {
        panic!("Call to robot_cleaning_interfaces__srv__BeginCoverage_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for BeginCoverage_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_cleaning_interfaces__srv__BeginCoverage_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_cleaning_interfaces__srv__BeginCoverage_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_cleaning_interfaces__srv__BeginCoverage_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for BeginCoverage_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for BeginCoverage_Response where Self: Sized {
  const TYPE_NAME: &'static str = "robot_cleaning_interfaces/srv/BeginCoverage_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__robot_cleaning_interfaces__srv__BeginCoverage_Response() }
  }
}


#[link(name = "robot_cleaning_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__robot_cleaning_interfaces__srv__PlanCoverage_Request() -> *const std::ffi::c_void;
}

#[link(name = "robot_cleaning_interfaces__rosidl_generator_c")]
extern "C" {
    fn robot_cleaning_interfaces__srv__PlanCoverage_Request__init(msg: *mut PlanCoverage_Request) -> bool;
    fn robot_cleaning_interfaces__srv__PlanCoverage_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<PlanCoverage_Request>, size: usize) -> bool;
    fn robot_cleaning_interfaces__srv__PlanCoverage_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<PlanCoverage_Request>);
    fn robot_cleaning_interfaces__srv__PlanCoverage_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<PlanCoverage_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<PlanCoverage_Request>) -> bool;
}

// Corresponds to robot_cleaning_interfaces__srv__PlanCoverage_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct PlanCoverage_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub regions: rosidl_runtime_rs::Sequence<rosidl_runtime_rs::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub start: geometry_msgs::msg::rmw::PoseStamped,


    // This member is not documented.
    #[allow(missing_docs)]
    pub gap_fill: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub target_coverage: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub distance_budget_m: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub covered: nav_msgs::msg::rmw::OccupancyGrid,


    // This member is not documented.
    #[allow(missing_docs)]
    pub excluded: rosidl_runtime_rs::Sequence<geometry_msgs::msg::rmw::Point>,

}



impl Default for PlanCoverage_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !robot_cleaning_interfaces__srv__PlanCoverage_Request__init(&mut msg as *mut _) {
        panic!("Call to robot_cleaning_interfaces__srv__PlanCoverage_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for PlanCoverage_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_cleaning_interfaces__srv__PlanCoverage_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_cleaning_interfaces__srv__PlanCoverage_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_cleaning_interfaces__srv__PlanCoverage_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for PlanCoverage_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for PlanCoverage_Request where Self: Sized {
  const TYPE_NAME: &'static str = "robot_cleaning_interfaces/srv/PlanCoverage_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__robot_cleaning_interfaces__srv__PlanCoverage_Request() }
  }
}


#[link(name = "robot_cleaning_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__robot_cleaning_interfaces__srv__PlanCoverage_Response() -> *const std::ffi::c_void;
}

#[link(name = "robot_cleaning_interfaces__rosidl_generator_c")]
extern "C" {
    fn robot_cleaning_interfaces__srv__PlanCoverage_Response__init(msg: *mut PlanCoverage_Response) -> bool;
    fn robot_cleaning_interfaces__srv__PlanCoverage_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<PlanCoverage_Response>, size: usize) -> bool;
    fn robot_cleaning_interfaces__srv__PlanCoverage_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<PlanCoverage_Response>);
    fn robot_cleaning_interfaces__srv__PlanCoverage_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<PlanCoverage_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<PlanCoverage_Response>) -> bool;
}

// Corresponds to robot_cleaning_interfaces__srv__PlanCoverage_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct PlanCoverage_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub reason: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub path: nav_msgs::msg::rmw::Path,

}



impl Default for PlanCoverage_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !robot_cleaning_interfaces__srv__PlanCoverage_Response__init(&mut msg as *mut _) {
        panic!("Call to robot_cleaning_interfaces__srv__PlanCoverage_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for PlanCoverage_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_cleaning_interfaces__srv__PlanCoverage_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_cleaning_interfaces__srv__PlanCoverage_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_cleaning_interfaces__srv__PlanCoverage_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for PlanCoverage_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for PlanCoverage_Response where Self: Sized {
  const TYPE_NAME: &'static str = "robot_cleaning_interfaces/srv/PlanCoverage_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__robot_cleaning_interfaces__srv__PlanCoverage_Response() }
  }
}






#[link(name = "robot_cleaning_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__robot_cleaning_interfaces__srv__BeginCoverage() -> *const std::ffi::c_void;
}

// Corresponds to robot_cleaning_interfaces__srv__BeginCoverage
#[allow(missing_docs, non_camel_case_types)]
pub struct BeginCoverage;

impl rosidl_runtime_rs::Service for BeginCoverage {
    type Request = BeginCoverage_Request;
    type Response = BeginCoverage_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__robot_cleaning_interfaces__srv__BeginCoverage() }
    }
}




#[link(name = "robot_cleaning_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__robot_cleaning_interfaces__srv__PlanCoverage() -> *const std::ffi::c_void;
}

// Corresponds to robot_cleaning_interfaces__srv__PlanCoverage
#[allow(missing_docs, non_camel_case_types)]
pub struct PlanCoverage;

impl rosidl_runtime_rs::Service for PlanCoverage {
    type Request = PlanCoverage_Request;
    type Response = PlanCoverage_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__robot_cleaning_interfaces__srv__PlanCoverage() }
    }
}


