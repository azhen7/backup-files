#ifndef _STD_COPY_SYSTEM_ERROR
#define _STD_COPY_SYSTEM_ERROR

#include <cerrno>

namespace std_copy
{
    enum class errc
    {
        address_family_not_supported = EAFNOSUPPORT,
        address_in_use = EADDRINUSE,
        address_not_available = EADDRNOTAVAIL,
        already_connected = EISCONN,
        argument_list_too_long = E2BIG,
        argument_out_of_domain = EDOM,
        bad_address = EFAULT,
        bad_file_descriptor = EBADF,
#ifdef EBADMSG
        bad_message = EBADMSG,
#endif
        broken_pipe = EPIPE,
        connection_aborted = ECONNABORTED,
        connection_already_in_progress = EALREADY,
        connection_refused = ECONNREFUSED,
        connection_reset = ECONNRESET,
        cross_device_link = EXDEV,
        destination_address_required = EDESTADDRREQ,
        device_or_resource_busy = EBUSY,
        directory_not_empty = ENOTEMPTY,
        executable_format_error = ENOEXEC,
        file_exists = EEXIST,
        file_too_large = EFBIG,
        filename_too_long = ENAMETOOLONG,
        function_not_supported = ENOSYS,
        host_unreachable = EHOSTUNREACH,
#ifdef EIDRM
        identifier_removed = EIDRM,
#endif
        illegal_byte_sequence = EILSEQ,
        inappropriate_io_control_operation = ENOTTY,
        interrupted = EINTR,
        invalid_argument = EINVAL,
        invalid_seek = ESPIPE,
        io_error = EIO,
        is_a_directory = EISDIR,
        message_size = EMSGSIZE,
        network_down = ENETDOWN,
        network_reset = ENETRESET,
        network_unreachable = ENETUNREACH,
        no_buffer_space = ENOBUFS,
#ifdef ECHILD
        no_child_process = ECHILD,
#endif
#ifdef ENOLINK
        no_link = ENOLINK,
#endif
        no_lock_available = ENOLCK,
#ifdef ENODATA
        no_message_available = ENODATA,
#endif
#ifdef ENOMSG
        no_message = ENOMSG,
#endif
        no_protocol_option = ENOPROTOOPT,
#ifdef ENOSPC
        no_space_on_device = ENOSPC,
#endif
#ifdef ENOSR
        no_stream_resources = ENOSR,
#endif
        no_such_device_or_address = ENXIO,
        no_such_device = ENODEV,
        no_such_file_or_directory = ENOENT,
        no_such_process = ESRCH,
        not_a_directory = ENOTDIR,
        not_a_socket = ENOTSOCK,
#ifdef ENOSTR
        not_a_stream = ENOSTR,
#endif
        not_connected = ENOTCONN,
        not_enough_memory = ENOMEM,
#ifdef ENOTSUP
        not_supported = ENOTSUP,
#endif
        operation_canceled = ECANCELED,
        operation_in_progress = EINPROGRESS,
#ifdef EPERM
        operation_not_permitted = EPERM,
#endif
        operation_not_supported = EOPNOTSUPP,
#ifdef EWOULDBLOCK
        operation_would_block = EWOULDBLOCK,
#endif
#ifdef EOWNERDEAD
        owner_dead = EOWNERDEAD,
#endif
        permission_denied = EACCES,
        protocol_error = EPROTO,
        protocol_not_supported = EPROTONOSUPPORT,
        read_only_file_system = EROFS,
        resource_deadlock_would_occur = EDEADLK,
        resource_unavailable_try_again = EAGAIN,
        result_out_of_range = ERANGE,
#ifdef ENOTRECOVERABLE
        state_not_recoverable = ENOTRECOVERABLE,
#endif
#ifdef ETIME
        stream_timeout = ETIME,
#endif
#ifdef ETXTBSY
        text_file_busy = ETXTBSY,
#endif
#ifdef ETIMEDOUT
        timed_out = ETIMEDOUT,
#endif
        too_many_files_open_in_system = ENFILE,
        too_many_files_open = EMFILE,
        too_many_links = EMLINK,
        too_many_symbolic_link_levels = ELOOP,
#ifdef EOVERFLOW
        value_too_large = EOVERFLOW,
#endif
        wrong_protocol_type = EPROTOTYPE
    };
}

#endif /* _STD_COPY_SYSTEM_ERROR */