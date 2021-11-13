// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: login_request.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_login_5frequest_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_login_5frequest_2eproto

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
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_login_5frequest_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_login_5frequest_2eproto {
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
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_login_5frequest_2eproto;
namespace auth {
class LoginRequest;
struct LoginRequestDefaultTypeInternal;
extern LoginRequestDefaultTypeInternal _LoginRequest_default_instance_;
}  // namespace auth
PROTOBUF_NAMESPACE_OPEN
template<> ::auth::LoginRequest* Arena::CreateMaybeMessage<::auth::LoginRequest>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace auth {

// ===================================================================

class LoginRequest final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:auth.LoginRequest) */ {
 public:
  inline LoginRequest() : LoginRequest(nullptr) {}
  ~LoginRequest() override;
  explicit constexpr LoginRequest(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  LoginRequest(const LoginRequest& from);
  LoginRequest(LoginRequest&& from) noexcept
    : LoginRequest() {
    *this = ::std::move(from);
  }

  inline LoginRequest& operator=(const LoginRequest& from) {
    CopyFrom(from);
    return *this;
  }
  inline LoginRequest& operator=(LoginRequest&& from) noexcept {
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
  static const LoginRequest& default_instance() {
    return *internal_default_instance();
  }
  static inline const LoginRequest* internal_default_instance() {
    return reinterpret_cast<const LoginRequest*>(
               &_LoginRequest_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(LoginRequest& a, LoginRequest& b) {
    a.Swap(&b);
  }
  inline void Swap(LoginRequest* other) {
    if (other == this) return;
    if (GetOwningArena() == other->GetOwningArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(LoginRequest* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline LoginRequest* New() const final {
    return new LoginRequest();
  }

  LoginRequest* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<LoginRequest>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const LoginRequest& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom(const LoginRequest& from);
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
  void InternalSwap(LoginRequest* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "auth.LoginRequest";
  }
  protected:
  explicit LoginRequest(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kEmailFieldNumber = 2,
    kPasswordFieldNumber = 3,
    kRequestIdFieldNumber = 1,
  };
  // required string email = 2;
  bool has_email() const;
  private:
  bool _internal_has_email() const;
  public:
  void clear_email();
  const std::string& email() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_email(ArgT0&& arg0, ArgT... args);
  std::string* mutable_email();
  PROTOBUF_MUST_USE_RESULT std::string* release_email();
  void set_allocated_email(std::string* email);
  private:
  const std::string& _internal_email() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_email(const std::string& value);
  std::string* _internal_mutable_email();
  public:

  // required string password = 3;
  bool has_password() const;
  private:
  bool _internal_has_password() const;
  public:
  void clear_password();
  const std::string& password() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_password(ArgT0&& arg0, ArgT... args);
  std::string* mutable_password();
  PROTOBUF_MUST_USE_RESULT std::string* release_password();
  void set_allocated_password(std::string* password);
  private:
  const std::string& _internal_password() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_password(const std::string& value);
  std::string* _internal_mutable_password();
  public:

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

  // @@protoc_insertion_point(class_scope:auth.LoginRequest)
 private:
  class _Internal;

  // helper for ByteSizeLong()
  size_t RequiredFieldsByteSizeFallback() const;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::internal::HasBits<1> _has_bits_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr email_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr password_;
  ::PROTOBUF_NAMESPACE_ID::int32 requestid_;
  friend struct ::TableStruct_login_5frequest_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// LoginRequest

// required int32 requestId = 1;
inline bool LoginRequest::_internal_has_requestid() const {
  bool value = (_has_bits_[0] & 0x00000004u) != 0;
  return value;
}
inline bool LoginRequest::has_requestid() const {
  return _internal_has_requestid();
}
inline void LoginRequest::clear_requestid() {
  requestid_ = 0;
  _has_bits_[0] &= ~0x00000004u;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 LoginRequest::_internal_requestid() const {
  return requestid_;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 LoginRequest::requestid() const {
  // @@protoc_insertion_point(field_get:auth.LoginRequest.requestId)
  return _internal_requestid();
}
inline void LoginRequest::_internal_set_requestid(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _has_bits_[0] |= 0x00000004u;
  requestid_ = value;
}
inline void LoginRequest::set_requestid(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _internal_set_requestid(value);
  // @@protoc_insertion_point(field_set:auth.LoginRequest.requestId)
}

// required string email = 2;
inline bool LoginRequest::_internal_has_email() const {
  bool value = (_has_bits_[0] & 0x00000001u) != 0;
  return value;
}
inline bool LoginRequest::has_email() const {
  return _internal_has_email();
}
inline void LoginRequest::clear_email() {
  email_.ClearToEmpty();
  _has_bits_[0] &= ~0x00000001u;
}
inline const std::string& LoginRequest::email() const {
  // @@protoc_insertion_point(field_get:auth.LoginRequest.email)
  return _internal_email();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void LoginRequest::set_email(ArgT0&& arg0, ArgT... args) {
 _has_bits_[0] |= 0x00000001u;
 email_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:auth.LoginRequest.email)
}
inline std::string* LoginRequest::mutable_email() {
  std::string* _s = _internal_mutable_email();
  // @@protoc_insertion_point(field_mutable:auth.LoginRequest.email)
  return _s;
}
inline const std::string& LoginRequest::_internal_email() const {
  return email_.Get();
}
inline void LoginRequest::_internal_set_email(const std::string& value) {
  _has_bits_[0] |= 0x00000001u;
  email_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, value, GetArenaForAllocation());
}
inline std::string* LoginRequest::_internal_mutable_email() {
  _has_bits_[0] |= 0x00000001u;
  return email_.Mutable(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, GetArenaForAllocation());
}
inline std::string* LoginRequest::release_email() {
  // @@protoc_insertion_point(field_release:auth.LoginRequest.email)
  if (!_internal_has_email()) {
    return nullptr;
  }
  _has_bits_[0] &= ~0x00000001u;
  return email_.ReleaseNonDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArenaForAllocation());
}
inline void LoginRequest::set_allocated_email(std::string* email) {
  if (email != nullptr) {
    _has_bits_[0] |= 0x00000001u;
  } else {
    _has_bits_[0] &= ~0x00000001u;
  }
  email_.SetAllocated(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), email,
      GetArenaForAllocation());
  // @@protoc_insertion_point(field_set_allocated:auth.LoginRequest.email)
}

// required string password = 3;
inline bool LoginRequest::_internal_has_password() const {
  bool value = (_has_bits_[0] & 0x00000002u) != 0;
  return value;
}
inline bool LoginRequest::has_password() const {
  return _internal_has_password();
}
inline void LoginRequest::clear_password() {
  password_.ClearToEmpty();
  _has_bits_[0] &= ~0x00000002u;
}
inline const std::string& LoginRequest::password() const {
  // @@protoc_insertion_point(field_get:auth.LoginRequest.password)
  return _internal_password();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void LoginRequest::set_password(ArgT0&& arg0, ArgT... args) {
 _has_bits_[0] |= 0x00000002u;
 password_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:auth.LoginRequest.password)
}
inline std::string* LoginRequest::mutable_password() {
  std::string* _s = _internal_mutable_password();
  // @@protoc_insertion_point(field_mutable:auth.LoginRequest.password)
  return _s;
}
inline const std::string& LoginRequest::_internal_password() const {
  return password_.Get();
}
inline void LoginRequest::_internal_set_password(const std::string& value) {
  _has_bits_[0] |= 0x00000002u;
  password_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, value, GetArenaForAllocation());
}
inline std::string* LoginRequest::_internal_mutable_password() {
  _has_bits_[0] |= 0x00000002u;
  return password_.Mutable(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, GetArenaForAllocation());
}
inline std::string* LoginRequest::release_password() {
  // @@protoc_insertion_point(field_release:auth.LoginRequest.password)
  if (!_internal_has_password()) {
    return nullptr;
  }
  _has_bits_[0] &= ~0x00000002u;
  return password_.ReleaseNonDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArenaForAllocation());
}
inline void LoginRequest::set_allocated_password(std::string* password) {
  if (password != nullptr) {
    _has_bits_[0] |= 0x00000002u;
  } else {
    _has_bits_[0] &= ~0x00000002u;
  }
  password_.SetAllocated(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), password,
      GetArenaForAllocation());
  // @@protoc_insertion_point(field_set_allocated:auth.LoginRequest.password)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace auth

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_login_5frequest_2eproto