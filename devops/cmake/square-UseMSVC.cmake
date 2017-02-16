macro(Config_MSVC)

    Define_MSVC()
    Settings_MSVC()
    # Deploy_MSVC()

endmacro(Config_MSVC)

# -----------------------------------------------------------
#    Directory Scope Command options for Build Flags (MSVC)
# ----------------------------------------------------------- [Build Flag Notes]

macro(Define_MSVC)

    add_definitions (

        -D_CRT_SECURE_NO_DEPRECATE      # Remove Debug CRT Deprecate Warnings
        -D_REENTRANT					# thread safe (i.e. re-entrant) versions
        -Oi								# intrinsic or otherwise functions
        -Ob2							# Controls inline expansion of functions.
        -MP								# reduces total build time
    )

endmacro(Define_MSVC)

# -----------------------------------------------------------
# Compiler Settings
# ----------------------------------------------------------- [Settings]

macro(Settings_MSVC)

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MT")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
    set(CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL} /MTd")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} /MTd")

endmacro(Settings_MSVC)


# -----------------------------------------------------------
# Move Files
# ----------------------------------------------------------- [Deploy]

macro(Deploy_MSVC)
# @todo
endmacro(Deploy_MSVC)


# -----------------------------------------------------------
# Notes
# ----------------------------------------------------------- [Build Flag Notes]

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MT")
# set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
# set(CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL} /MTd")
# set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} /MTd")
# set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")


# ----------------------------------------------------------- [CRT]

# [Secure Template Overloads for C Run-time Library (CRT)]
# https://msdn.microsoft.com/en-us/library/ms175759

# add_definitions(-_CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES1)    # enables template overloads of standard CRT functions that auto call more secure variants
# add_definitions(-D_CRT_SECURE_NO_DEPRECATE)                   # Remove Debug CRT Deprecate Warnings
# add_definitions(-_CRT_SECURE_NO_WARNING)                      # Remove all CRT warnings


# ----------------------------------------------------------- [Arch]

# [Arch (Minimum CPU Architecture)]
# https://msdn.microsoft.com/en-us/library/jj620900.aspx

# add_definitions(-arch:IA32)       # (x86) Specifies no enhanced instructions and also specifies x87 for floating-point calculations.
# add_definitions(-arch:SSE)        # (x86) Enables the use of SSE instructions.
# add_definitions(-arch:SSE2)       # (x86) Enables the use of SSE2 instructions. (Default instruction on x86 platforms if no /arch option)
# add_definitions(-arch:AVX)        # (x86/x64) Enables the use of Intel Advanced Vector Extensions instructions.
# add_definitions(-arch:AVX2)       # (x64) Enables the use of Intel Advanced Vector Extensions 2 instructions
# add_definitions(-arch:ARMv7VE)    # (ARM) Enables the use of ARMv7VE Virtualization Extensions instructions.
# add_definitions(-arch:VFPv4)      # (ARM) Enables the use of ARM VFPv4 instructions. If this option is not specified, VFPv3 is the default.


# ----------------------------------------------------------- [Optimize]

# [/O Options (Optimize Code)]
# https://msdn.microsoft.com/en-us/library/k1ack8f1.aspx
# https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html

# add_definitions(-O1)       # Creates the smallest code in the majority of cases.
			                 # equivalent to: /Og /Os /Oy /Ob2 /Gs /GF /Gy

# add_definitions(-O2)       # Creates the fastest code in the majority of cases. (Default setting for release builds)
			                 # Equivalent to: /Og /Oi /Ot /Oy /Ob2 /Gs /GF /Gy

# add_definitions(-Ox)       # Uses maximum optimization (Favors execution speed over smaller size).
                             # Equivalent to: /Ob / Og / Oi / Ot / Oy  # Mutually Excusive from: /O1 / O2 /Od

# add_definitions(-Oy)       # Suppresses the creation of frame pointers on the call stack for quicker function calls.

# add_definitions(-Oi)       # Replaces some function calls with intrinsic or otherwise special forms of the function that help your application run faster.

# add_definitions(-Ob2)      # Controls inline expansion of functions.


# ----------------------------------------------------------- [Misc]

# All Compile Options:
# https://msdn.microsoft.com/en-us/library/fwkeyyhe.aspx

# add_definitions(-Qfast_transcendentals)    # Generates fast transcendentals.
# add_definitions(-fPIE)                     # Address space layout randomization
# add_definitions(-pipe)
# add_definitions(-fno-exceptions)           # https://gcc.gnu.org/onlinedocs/libstdc++/manual/using_exceptions.html#intro.using.exception.no
# add_definitions(-Wall)                     # Enables all warnings, including warnings that are disabled by default.
# add_definitions(-w)                        # Disables all warnings.

# add_definitions(-D_REENTRANT)              # Compiler will use thread safe (i.e. re-entrant) versions of several functions in the C library

# add_definitions(-MP)                       # Enables the compiler to create one or more copies of itself, each in a separate process.
                                             # These copies simultaneously compile the source files, significantly reducing total build time.
