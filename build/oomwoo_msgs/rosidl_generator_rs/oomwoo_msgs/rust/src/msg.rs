#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



// Corresponds to oomwoo_msgs__msg__BumpEvent
/// A localized bump: where the vacuum physically touched something solid, and how
/// it got there. Built by the bump_map node from the two bumper switches + TF.
///
/// The bump map is the tactile keep-out layer: LiDAR/cameras see couch skirts, bed
/// valances and curtains as solid, but only a physical contact proves something is
/// truly solid, so a coverage planner can still clean under/through the rest.

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct BumpEvent {
    /// header.frame_id = map (or odom); stamp = bump time
    pub header: std_msgs::msg::Header,

    /// estimated contact point on the obstacle surface
    pub contact: geometry_msgs::msg::Point,

    /// robot base_footprint at the bump
    pub robot: geometry_msgs::msg::Point,

    /// robot base_footprint a moment before the bump
    pub approach: geometry_msgs::msg::Point,

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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::BumpEvent::default())
  }
}

impl rosidl_runtime_rs::Message for BumpEvent {
  type RmwMsg = super::msg::rmw::BumpEvent;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        contact: geometry_msgs::msg::Point::into_rmw_message(std::borrow::Cow::Owned(msg.contact)).into_owned(),
        robot: geometry_msgs::msg::Point::into_rmw_message(std::borrow::Cow::Owned(msg.robot)).into_owned(),
        approach: geometry_msgs::msg::Point::into_rmw_message(std::borrow::Cow::Owned(msg.approach)).into_owned(),
        heading: msg.heading,
        side: msg.side,
        left_depress: msg.left_depress,
        right_depress: msg.right_depress,
        left_rate: msg.left_rate,
        right_rate: msg.right_rate,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
        contact: geometry_msgs::msg::Point::into_rmw_message(std::borrow::Cow::Borrowed(&msg.contact)).into_owned(),
        robot: geometry_msgs::msg::Point::into_rmw_message(std::borrow::Cow::Borrowed(&msg.robot)).into_owned(),
        approach: geometry_msgs::msg::Point::into_rmw_message(std::borrow::Cow::Borrowed(&msg.approach)).into_owned(),
      heading: msg.heading,
      side: msg.side,
      left_depress: msg.left_depress,
      right_depress: msg.right_depress,
      left_rate: msg.left_rate,
      right_rate: msg.right_rate,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      contact: geometry_msgs::msg::Point::from_rmw_message(msg.contact),
      robot: geometry_msgs::msg::Point::from_rmw_message(msg.robot),
      approach: geometry_msgs::msg::Point::from_rmw_message(msg.approach),
      heading: msg.heading,
      side: msg.side,
      left_depress: msg.left_depress,
      right_depress: msg.right_depress,
      left_rate: msg.left_rate,
      right_rate: msg.right_rate,
    }
  }
}


