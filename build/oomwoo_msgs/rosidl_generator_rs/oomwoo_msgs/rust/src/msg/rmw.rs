#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};


#[link(name = "oomwoo_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__oomwoo_msgs__msg__BumpEvent() -> *const std::ffi::c_void;
}

#[link(name = "oomwoo_msgs__rosidl_generator_c")]
extern "C" {
    fn oomwoo_msgs__msg__BumpEvent__init(msg: *mut BumpEvent) -> bool;
    fn oomwoo_msgs__msg__BumpEvent__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<BumpEvent>, size: usize) -> bool;
    fn oomwoo_msgs__msg__BumpEvent__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<BumpEvent>);
    fn oomwoo_msgs__msg__BumpEvent__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<BumpEvent>, out_seq: *mut rosidl_runtime_rs::Sequence<BumpEvent>) -> bool;
}

// Corresponds to oomwoo_msgs__msg__BumpEvent
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// A localized bump: where the vacuum physically touched something solid, and how
/// it got there. Built by the bump_map node from the two bumper switches + TF.
///
/// The bump map is the tactile keep-out layer: LiDAR/cameras see couch skirts, bed
/// valances and curtains as solid, but only a physical contact proves something is
/// truly solid, so a coverage planner can still clean under/through the rest.

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct BumpEvent {
    /// header.frame_id = map (or odom); stamp = bump time
    pub header: std_msgs::msg::rmw::Header,

    /// estimated contact point on the obstacle surface
    pub contact: geometry_msgs::msg::rmw::Point,

    /// robot base_footprint at the bump
    pub robot: geometry_msgs::msg::rmw::Point,

    /// robot base_footprint a moment before the bump
    pub approach: geometry_msgs::msg::rmw::Point,

    /// robot heading at the bump (rad, in header.frame_id)
    pub heading: f64,

    /// which bumper switch(es) fired (see constants)
    pub side: u8,

    /// Richer signal from optical-interrupter bumpers; all 0.0 when only the binary
    /// left/right switches are available (current sim + simplest hardware). *_depress
    /// is 0..1 (how far that side is pressed); *_rate is the press rate (1/s). The
    /// left/right depress RATIO estimates the contact angle within the arc, replacing
    /// the geometric guess bump_map makes from binary switches.
    pub left_depress: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub right_depress: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub left_rate: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub right_rate: f32,

}

impl BumpEvent {

    // This constant is not documented.
    #[allow(missing_docs)]
    pub const SIDE_BOTH: u8 = 0;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const SIDE_LEFT: u8 = 1;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const SIDE_RIGHT: u8 = 2;

}


impl Default for BumpEvent {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !oomwoo_msgs__msg__BumpEvent__init(&mut msg as *mut _) {
        panic!("Call to oomwoo_msgs__msg__BumpEvent__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for BumpEvent {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { oomwoo_msgs__msg__BumpEvent__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { oomwoo_msgs__msg__BumpEvent__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { oomwoo_msgs__msg__BumpEvent__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for BumpEvent {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for BumpEvent where Self: Sized {
  const TYPE_NAME: &'static str = "oomwoo_msgs/msg/BumpEvent";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__oomwoo_msgs__msg__BumpEvent() }
  }
}


