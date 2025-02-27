/*
$info$
tags: thunklibs|X11
desc: Handles callbacks and varargs
$end_info$
*/

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xresource.h>

#include <stdio.h>
#include <cstring>
#include <map>
#include <string>

#include "common/Guest.h"
#include <stdarg.h>

#include "callback_typedefs.inl"

#include "thunks.inl"
#include "function_packs.inl"
#include "function_packs_public.inl"

#include "callback_unpacks.inl"

// Custom implementations //

#include <vector>

extern "C" {
    char* XGetICValues(XIC ic, ...) {
        fprintf(stderr, "XGetICValues\n");
        va_list ap;
        std::vector<unsigned long> args;
        va_start(ap, ic);
        for (;;) {
            auto arg = va_arg(ap, unsigned long);
            if (arg == 0)
                break;
            args.push_back(arg);
            fprintf(stderr, "%016lX\n", arg);
        }

        va_end(ap);
        auto rv = fexfn_pack_XGetICValues_internal(ic, args.size(), &args[0]);
        fprintf(stderr, "RV: %p\n", rv);
        return rv;
    }

    _XIC* XCreateIC(XIM im, ...) {
        fprintf(stderr, "XCreateIC\n");
        va_list ap;
        std::vector<unsigned long> args;
        va_start(ap, im);
        for (;;) {
            auto arg = va_arg(ap, unsigned long);
            if (arg == 0)
                break;
            args.push_back(arg);
            fprintf(stderr, "%016lX\n", arg);
        }

        va_end(ap);
        auto rv = fexfn_pack_XCreateIC_internal(im, args.size(), &args[0]);
        fprintf(stderr, "RV: %p\n", rv);
        return rv;
    }

    int XIfEvent(Display* a0, XEvent* a1, XIfEventCBFN* a2, XPointer a3) {
        return fexfn_pack_XIfEvent_internal(a0, a1, a2, a3);
    }

    XSetErrorHandlerCBFN* XSetErrorHandler(XErrorHandler a_0) {
        return fexfn_pack_XSetErrorHandler_internal(a_0);
    }

    int (*XESetCloseDisplay(Display *display, int extension, int (*proc)()))() {
        fprintf(stderr, "libX11: XESetCloseDisplay\n");
        return nullptr;
    }

    static void LockMutexFunction() {
      fprintf(stderr, "libX11: LockMutex\n");
    }

    static void UnlockMutexFunction() {
      fprintf(stderr, "libX11: LockMutex\n");
    }

  void (*_XLockMutex_fn)() = LockMutexFunction;
  void (*_XUnlockMutex_fn)() = UnlockMutexFunction;
  typedef struct _LockInfoRec *LockInfoPtr;
  LockInfoPtr _Xglobal_lock = (LockInfoPtr)0x4142434445464748ULL;
}

struct {
    #include "callback_unpacks_header.inl"
} callback_unpacks = {
    #include "callback_unpacks_header_init.inl"
};

LOAD_LIB_WITH_CALLBACKS(libX11)
