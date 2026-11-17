#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};




// Corresponds to oomwoo_localization_msgs__srv__Relocalize_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Relocalize_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub structure_needs_at_least_one_member: u8,

}



impl Default for Relocalize_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::Relocalize_Request::default())
  }
}

impl rosidl_runtime_rs::Message for Relocalize_Request {
  type RmwMsg = super::srv::rmw::Relocalize_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        structure_needs_at_least_one_member: msg.structure_needs_at_least_one_member,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      structure_needs_at_least_one_member: msg.structure_needs_at_least_one_member,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      structure_needs_at_least_one_member: msg.structure_needs_at_least_one_member,
    }
  }
}


// Corresponds to oomwoo_localization_msgs__srv__Relocalize_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Relocalize_Response {
    /// confident, accepted fix
    pub success: bool,

    /// best base-frame pose in map
    pub pose: geometry_msgs::msg::PoseWithCovarianceStamped,

    /// summed match score
    pub score: f32,

    /// score / n_beams, in [0, 1]
    pub score_normalized: f32,

    /// (top1 - top2) / top1, in [0, 1]
    pub confidence: f32,

    /// search wall-clock time
    pub runtime_s: f32,

    /// human-readable summary
    pub message: std::string::String,

}



impl Default for Relocalize_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::Relocalize_Response::default())
  }
}

impl rosidl_runtime_rs::Message for Relocalize_Response {
  type RmwMsg = super::srv::rmw::Relocalize_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        success: msg.success,
        pose: geometry_msgs::msg::PoseWithCovarianceStamped::into_rmw_message(std::borrow::Cow::Owned(msg.pose)).into_owned(),
        score: msg.score,
        score_normalized: msg.score_normalized,
        confidence: msg.confidence,
        runtime_s: msg.runtime_s,
        message: msg.message.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      success: msg.success,
        pose: geometry_msgs::msg::PoseWithCovarianceStamped::into_rmw_message(std::borrow::Cow::Borrowed(&msg.pose)).into_owned(),
      score: msg.score,
      score_normalized: msg.score_normalized,
      confidence: msg.confidence,
      runtime_s: msg.runtime_s,
        message: msg.message.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      success: msg.success,
      pose: geometry_msgs::msg::PoseWithCovarianceStamped::from_rmw_message(msg.pose),
      score: msg.score,
      score_normalized: msg.score_normalized,
      confidence: msg.confidence,
      runtime_s: msg.runtime_s,
      message: msg.message.to_string(),
    }
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


