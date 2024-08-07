// bdls_pipeutil.h                                                    -*-C++-*-

// ----------------------------------------------------------------------------
//                                   NOTICE
//
// This component is not up to date with current BDE coding standards, and
// should not be used as an example for new development.
// ----------------------------------------------------------------------------

#ifndef INCLUDED_BDLS_PIPEUTIL
#define INCLUDED_BDLS_PIPEUTIL

#include <bsls_ident.h>
BSLS_IDENT("$Id: $")

//@PURPOSE: Provide basic portable named-pipe utilities.
//
//@CLASSES:
//  bdls::PipeUtil: Portable utility methods for naming and accessing pipes
//
//@SEE_ALSO:
//
//@DESCRIPTION: This component, 'bdls::PipeUtil', provides portable utility
// methods for named pipes.

#include <bdlscm_version.h>

#include <bsl_string.h>
#include <bsl_string_view.h>

#include <bsls_libraryfeatures.h>

#ifdef BSLS_LIBRARYFEATURES_HAS_CPP17_PMR
#include <memory_resource>  // 'std::pmr::polymorphic_allocator'
#endif

#include <string>           // 'std::string', 'std::pmr::string'

namespace BloombergLP {

namespace bdls {
                              // ===============
                              // struct PipeUtil
                              // ===============
struct PipeUtil {
    // This struct contains utility methods for platform-independent named pipe
    // operations.

    static int makeCanonicalName(bsl::string             *pipeName,
                                 const bsl::string_view&  baseName);
    static int makeCanonicalName(std::string             *pipeName,
                                 const bsl::string_view&  baseName);
#ifdef BSLS_LIBRARYFEATURES_HAS_CPP17_PMR
    static int makeCanonicalName(std::pmr::string        *pipeName,
                                 const bsl::string_view&  baseName);
#endif
        // Load into the specified 'pipeName' the system-dependent canonical
        // pipe name corresponding to the specified 'baseName'.  Return 0 on
        // success, and a nonzero value if 'baseName' cannot be part of a pipe
        // name on this system.  On Unix systems, if 'baseName' is not a full
        // path name, the canonical name will be prefixed with the directory
        // specified by the 'SOCKDIR' environment variable if it is set,
        // otherwise with the directory specified by the 'TMPDIR' environment
        // variable if it is set, and otherwise by the current directory.  On
        // Windows systems, if 'baseName' is not a full path name, the
        // canonical name will be prefixed with "\\.\pipe\".

    static int send(const bsl::string_view& pipeName,
                    const bsl::string_view& message);
        // Send the specified 'message' to the pipe with the specified UTF-8
        // 'pipeName'.  Return 0 on success, and a nonzero value otherwise.
        // The behavior is undefined unless 'pipeName' is a valid UTF-8 string.

    static bool isOpenForReading(const bsl::string_view& pipeName);
        // Return 'true' if the pipe with the specified UTF-8 'pipeName' exists
        // and is currently open for reading by some process, and 'false'
        // otherwise.  The behavior is undefined unless 'pipeName' is a valid
        // UTF-8 string.
};

}  // close package namespace
}  // close enterprise namespace

#endif

// ----------------------------------------------------------------------------
// Copyright 2015 Bloomberg Finance L.P.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// ----------------------------- END-OF-FILE ----------------------------------
