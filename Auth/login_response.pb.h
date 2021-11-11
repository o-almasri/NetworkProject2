// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: login_response.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_login_5fresponse_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_login_5fresponse_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3018000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3018000 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_login_5fresponse_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_login_5fresponse_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxiliaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[1]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_login_5fresponse_2eproto;
namespace auth {
class LoginResponse;
struct LoginResponseDefaultTypeInternal;
extern LoginResponseDefaultTypeInternal _LoginResponse_default_instance_;
}  // namespace auth
PROTOBUF_NAMESPACE_OPEN
template<> ::auth::LoginResponse* Arena::CreateMaybeMessage<::auth::LoginResponse>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace auth {

enum LoginResponse_eAuthResultType : int {
  LoginResponse_eAuthResultType_SUCCESS = 0,
  LoginResponse_eAuthResultType_INVALID_PASSWORD = 1,
  LoginResponse_eAuthResultType_EMAIL_NOT_FOUND = 2,
  LoginResponse_eAuthResultType_INTERNAL_SERVER_ERROR = 3
};
bool LoginResponse_eAuthResultType_IsValid(int value);
constexpr LoginResponse_eAuthResultType LoginResponse_eAuthResultType_eAuthResultType_MIN = LoginResponse_eAuthResultType_SUCCESS;
constexpr LoginResponse_eAuthResultType LoginResponse_eAuthResultType_eAuthResultType_MAX = LoginResponse_eAuthResultType_INTERNAL_SERVER_ERROR;
constexpr int LoginResponse_eAuthResultType_eAuthResultType_ARRAYSIZE = LoginResponse_eAuthResultType_eAuthResultType_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* LoginResponse_eAuthResultType_descriptor();
template<typename T>
inline const std::string& LoginResponse_eAuthResultType_Name(T enum_t_value) {
  static_assert(::std::is_same<T, LoginResponse_eAuthResultType>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function LoginResponse_eAuthResultType_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    LoginResponse_eAuthResultType_descriptor(), enum_t_value);
}
inline bool LoginResponse_eAuthResultType_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, LoginResponse_eAuthResultType* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<LoginResponse_eAuthResultType>(
    LoginResponse_eAuthResultType_descriptor(), name, value);
}
// ===================================================================

class LoginResponse final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:auth.LoginResponse) */ {
 public:
  inline LoginResponse() : LoginResponse(nullptr) {}
  ~LoginResponse() override;
  explicit constexpr LoginResponse(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  LoginResponse(const LoginResponse& from);
  LoginResponse(LoginResponse&& from) noexcept
    : LoginResponse() {
    *this = ::std::move(from);
  }

  inline LoginResponse& operator=(const LoginResponse& from) {
    CopyFrom(from);
    return *this;
  }
  inline LoginResponse& operator=(LoginResponse&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance);
  }
  inline ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const LoginResponse& default_instance() {
    return *internal_default_instance();
  }
  static inline const LoginResponse* internal_default_instance() {
    return reinterpret_cast<const LoginResponse*>(
               &_LoginResponse_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(LoginResponse& a, LoginResponse& b) {
    a.Swap(&b);
  }
  inline void Swap(LoginResponse* other) {
    if (other == this) return;
    if (GetOwningArena() == other->GetOwningArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(LoginResponse* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline LoginResponse* New() const final {
    return new LoginResponse();
  }

  LoginResponse* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<LoginResponse>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const LoginResponse& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom(const LoginResponse& from);
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to, const ::PROTOBUF_NAMESPACE_ID::Message& from);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(LoginResponse* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "auth.LoginResponse";
  }
  protected:
  explicit LoginResponse(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  typedef LoginResponse_eAuthResultType eAuthResultType;
  static constexpr eAuthResultType SUCCESS =
    LoginResponse_eAuthResultType_SUCCESS;
  static constexpr eAuthResultType INVALID_PASSWORD =
    LoginResponse_eAuthResultType_INVALID_PASSWORD;
  static constexpr eAuthResultType EMAIL_NOT_FOUND =
    LoginResponse_eAuthResultType_EMAIL_NOT_FOUND;
  static constexpr eAuthResultType INTERNAL_SERVER_ERROR =
    LoginResponse_eAuthResultType_INTERNAL_SERVER_ERROR;
  static inline bool eAuthResultType_IsValid(int value) {
    return LoginResponse_eAuthResultType_IsValid(value);
  }
  static constexpr eAuthResultType eAuthResultType_MIN =
    LoginResponse_eAuthResultType_eAuthResultType_MIN;
  static constexpr eAuthResultType eAuthResultType_MAX =
    LoginResponse_eAuthResultType_eAuthResultType_MAX;
  static constexpr int eAuthResultType_ARRAYSIZE =
    LoginResponse_eAuthResultType_eAuthResultType_ARRAYSIZE;
  static inline const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor*
  eAuthResultType_descriptor() {
    return LoginResponse_eAuthResultType_descriptor();
  }
  template<typename T>
  static inline const std::string& eAuthResultType_Name(T enum_t_value) {
    static_assert(::std::is_same<T, eAuthResultType>::value ||
      ::std::is_integral<T>::value,
      "Incorrect type passed to function eAuthResultType_Name.");
    return LoginResponse_eAuthResultType_Name(enum_t_value);
  }
  static inline bool eAuthResultType_Parse(::PROTOBUF_NAMESPACE_ID::ConstStringParam name,
      eAuthResultType* value) {
    return LoginResponse_eAuthResultType_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  enum : int {
    kRequestIdFieldNumber = 1,
    kUserIdFieldNumber = 2,
    kResultFieldNumber = 3,
  };
  // required int32 requestId = 1;
  bool has_requestid() const;
  private:
  bool _internal_has_requestid() const;
  public:
  void clear_requestid();
  ::PROTOBUF_NAMESPACE_ID::int32 requestid() const;
  void set_requestid(::PROTOBUF_NAMESPACE_ID::int32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int32 _internal_requestid() const;
  void _internal_set_requestid(::PROTOBUF_NAMESPACE_ID::int32 value);
  public:

  // required int32 userId = 2;
  bool has_userid() const;
  private:
  bool _internal_has_userid() const;
  public:
  void clear_userid();
  ::PROTOBUF_NAMESPACE_ID::int32 userid() const;
  void set_userid(::PROTOBUF_NAMESPACE_ID::int32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int32 _internal_userid() const;
  void _internal_set_userid(::PROTOBUF_NAMESPACE_ID::int32 value);
  public:

  // required .auth.LoginResponse.eAuthResultType result = 3;
  bool has_result() const;
  private:
  bool _internal_has_result() const;
  public:
  void clear_result();
  ::auth::LoginResponse_eAuthResultType result() const;
  void set_result(::auth::LoginResponse_eAuthResultType value);
  private:
  ::auth::LoginResponse_eAuthResultType _internal_result() const;
  void _internal_set_result(::auth::LoginResponse_eAuthResultType value);
  public:

  // @@protoc_insertion_point(class_scope:auth.LoginResponse)
 private:
  class _Internal;

  // helper for ByteSizeLong()
  size_t RequiredFieldsByteSizeFallback() const;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::internal::HasBits<1> _has_bits_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  ::PROTOBUF_NAMESPACE_ID::int32 requestid_;
  ::PROTOBUF_NAMESPACE_ID::int32 userid_;
  int result_;
  friend struct ::TableStruct_login_5fresponse_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// LoginResponse

// required int32 requestId = 1;
inline bool LoginResponse::_internal_has_requestid() const {
  bool value = (_has_bits_[0] & 0x00000001u) != 0;
  return value;
}
inline bool LoginResponse::has_requestid() const {
  return _internal_has_requestid();
}
inline void LoginResponse::clear_requestid() {
  requestid_ = 0;
  _has_bits_[0] &= ~0x00000001u;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 LoginResponse::_internal_requestid() const {
  return requestid_;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 LoginResponse::requestid() const {
  // @@protoc_insertion_point(field_get:auth.LoginResponse.requestId)
  return _internal_requestid();
}
inline void LoginResponse::_internal_set_requestid(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _has_bits_[0] |= 0x00000001u;
  requestid_ = value;
}
inline void LoginResponse::set_requestid(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _internal_set_requestid(value);
  // @@protoc_insertion_point(field_set:auth.LoginResponse.requestId)
}

// required int32 userId = 2;
inline bool LoginResponse::_internal_has_userid() const {
  bool value = (_has_bits_[0] & 0x00000002u) != 0;
  return value;
}
inline bool LoginResponse::has_userid() const {
  return _internal_has_userid();
}
inline void LoginResponse::clear_userid() {
  userid_ = 0;
  _has_bits_[0] &= ~0x00000002u;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 LoginResponse::_internal_userid() const {
  return userid_;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 LoginResponse::userid() const {
  // @@protoc_insertion_point(field_get:auth.LoginResponse.userId)
  return _internal_userid();
}
inline void LoginResponse::_internal_set_userid(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _has_bits_[0] |= 0x00000002u;
  userid_ = value;
}
inline void LoginResponse::set_userid(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _internal_set_userid(value);
  // @@protoc_insertion_point(field_set:auth.LoginResponse.userId)
}

// required .auth.LoginResponse.eAuthResultType result = 3;
inline bool LoginResponse::_internal_has_result() const {
  bool value = (_has_bits_[0] & 0x00000004u) != 0;
  return value;
}
inline bool LoginResponse::has_result() const {
  return _internal_has_result();
}
inline void LoginResponse::clear_result() {
  result_ = 0;
  _has_bits_[0] &= ~0x00000004u;
}
inline ::auth::LoginResponse_eAuthResultType LoginResponse::_internal_result() const {
  return static_cast< ::auth::LoginResponse_eAuthResultType >(result_);
}
inline ::auth::LoginResponse_eAuthResultType LoginResponse::result() const {
  // @@protoc_insertion_point(field_get:auth.LoginResponse.result)
  return _internal_result();
}
inline void LoginResponse::_internal_set_result(::auth::LoginResponse_eAuthResultType value) {
  assert(::auth::LoginResponse_eAuthResultType_IsValid(value));
  _has_bits_[0] |= 0x00000004u;
  result_ = value;
}
inline void LoginResponse::set_result(::auth::LoginResponse_eAuthResultType value) {
  _internal_set_result(value);
  // @@protoc_insertion_point(field_set:auth.LoginResponse.result)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace auth

PROTOBUF_NAMESPACE_OPEN

template <> struct is_proto_enum< ::auth::LoginResponse_eAuthResultType> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::auth::LoginResponse_eAuthResultType>() {
  return ::auth::LoginResponse_eAuthResultType_descriptor();
}

PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_login_5fresponse_2eproto
