#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



#[link(name = "oomwoo_localization_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__oomwoo_localization_msgs__srv__Relocalize_Request() -> *const std::ffi::c_void;
}

#[link(name = "oomwoo_localization_msgs__rosidl_generator_c")]
extern "C" {
    fn oomwoo_localization_msgs__srv__Relocalize_Request__init(msg: *mut Relocalize_Request) -> bool;
    fn oomwoo_localization_msgs__srv__Relocalize_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<Relocalize_Request>, size: usize) -> bool;
    fn oomwoo_localization_msgs__srv__Relocalize_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<Relocalize_Request>);
    fn oomwoo_localization_msgs__srv__Relocalize_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<Relocalize_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<Relocalize_Request>) -> bool;
}

// Corresponds to oomwoo_localization_msgs__srv__Relocalize_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Relocalize_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub structure_needs_at_least_one_member: u8,

}



impl Default for Relocalize_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !oomwoo_localization_msgs__srv__Relocalize_Request__init(&mut msg as *mut _) {
        panic!("Call to oomwoo_localization_msgs__srv__Relocalize_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for Relocalize_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { oomwoo_localization_msgs__srv__Relocalize_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { oomwoo_localization_msgs__srv__Relocalize_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { oomwoo_localization_msgs__srv__Relocalize_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for Relocalize_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for Relocalize_Request where Self: Sized {
  const TYPE_NAME: &'static str = "oomwoo_localization_msgs/srv/Relocalize_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__oomwoo_localization_msgs__srv__Relocalize_Request() }
  }
}


#[link(name = "oomwoo_localization_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__oomwoo_localization_msgs__srv__Relocalize_Response() -> *const std::ffi::c_void;
}

#[link(name = "oomwoo_localization_msgs__rosidl_generator_c")]
extern "C" {
    fn oomwoo_localization_msgs__srv__Relocalize_Response__init(msg: *mut Relocalize_Response) -> bool;
    fn oomwoo_localization_msgs__srv__Relocalize_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<Relocalize_Response>, size: usize) -> bool;
    fn oomwoo_localization_msgs__srv__Relocalize_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<Relocalize_Response>);
    fn oomwoo_localization_msgs__srv__Relocalize_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<Relocalize_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<Relocalize_Response>) -> bool;
}

// Corresponds to oomwoo_localization_msgs__srv__Relocalize_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Relocalize_Response {
    /// confident, accepted fix
    pub success: bool,

    /// best base-frame pose in map
    pub pose: geometry_msgs::msg::rmw::PoseWithCovarianceStamped,

    /// summed match score
    pub score: f32,

    /// score / n_beams, in [0, 1]
    pub score_normalized: f32,

    /// (top1 - top2) / top1, in [0, 1]
    pub confidence: f32,

    /// search wall-clock time
    pub runtime_s: f32,

    /// human-readable summary
    pub message: rosidl_runtime_rs::String,

}



impl Default for Relocalize_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !oomwoo_localization_msgs__srv__Relocalize_Response__init(&mut msg as *mut _) {
        panic!("Call to oomwoo_localization_msgs__srv__Relocalize_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for Relocalize_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { oomwoo_localization_msgs__srv__Relocalize_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { oomwoo_localization_msgs__srv__Relocalize_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { oomwoo_localization_msgs__srv__Relocalize_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for Relocalize_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for Relocalize_Response where Self: Sized {
  const TYPE_NAME: &'static str = "oomwoo_localization_msgs/srv/Relocalize_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__oomwoo_localization_msgs__srv__Relocalize_Response() }
  }
}






#[link(name = "oomwoo_localization_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__oomwoo_localization_msgs__srv__Relocalize() -> *const std::ffi::c_void;
}

// Corresponds to oomwoo_localization_msgs__srv__Relocalize
#[allow(missing_docs, non_camel_case_types)]
pub struct Relocalize;

impl rosidl_runtime_rs::Service for Relocalize {
    type Request = Relocalize_Request;
    type Response = Relocalize_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__oomwoo_localization_msgs__srv__Relocalize() }
    }
}


