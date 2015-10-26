#include "nsutil_posix_funcs.h"

using namespace std;
using namespace v8;

// handle sutil_posix
NAN_METHOD(nsutil_posix_getpriority_sync)
{
    Nan::HandleScope scope;
    if (info.Length() == 0) {
        Nan::ThrowTypeError("Wrong number of arguments");
        info.GetReturnValue().Set(Nan::Undefined());
    }
    if (!info[0]->IsNumber()) {
        Nan::ThrowTypeError("Wrong arguments");
        info.GetReturnValue().Set(Nan::Undefined());
    }
    int32_t pid = info[0]->Int32Value();
    int priority;
    if(sutil_posix_getpriority(pid, priority) == -1) {
        info.GetReturnValue().Set(Nan::Undefined());
    }

    info.GetReturnValue().Set(Nan::New<Number>(priority));
}

NAN_METHOD(nsutil_posix_setpriority_sync)
{
    Nan::HandleScope scope;
    if (info.Length() != 2) {
        Nan::ThrowTypeError("Wrong number of arguments");
        info.GetReturnValue().Set(Nan::Undefined());
    }
    if (!info[0]->IsNumber() || !info[1]->IsNumber()) {
        Nan::ThrowTypeError("Wrong arguments");
        info.GetReturnValue().Set(Nan::Undefined());
    }
    int32_t pid = info[0]->Int32Value();
    int priority = info[0]->IntegerValue();
    if(sutil_posix_setpriority(pid, priority) == -1) {
        Nan::ThrowTypeError("SetPriority Error");
    }

    info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(nsutil_posix_statvfs)
{
    Nan::HandleScope scope;
    if (info.Length() != 1) {
        Nan::ThrowTypeError("Wrong number of arguments");
        info.GetReturnValue().Set(Nan::Undefined());
    }
    if (!info[0]->IsString()) {
        Nan::ThrowTypeError("Wrong arguments");
        info.GetReturnValue().Set(Nan::Undefined());
    }
    String::Utf8Value str(info[0]->ToString());
    char const *path = *str;
    struct statvfs buffer;
    int status = sutil_posix_statvfs(path, buffer);
    if (status) {
        info.GetReturnValue().Set(Nan::Undefined());
    }
    Local<Object> obj = Nan::New<Object>();
    obj->Set(Nan::New("bsize").ToLocalChecked(), 
            Nan::New<Number>(buffer.f_bsize));
    obj->Set(Nan::New("frsize"), 
            Nan::New<Number>(buffer.f_frsize));
    obj->Set(Nan::New("blocks").ToLocalChecked(), 
            Nan::New<Number>(buffer.f_blocks));
    obj->Set(Nan::New("bfree").ToLocalChecked(), 
            Nan::New<Number>(buffer.f_bfree));
    obj->Set(Nan::New("bavail").ToLocalChecked(), 
            Nan::New<Number>(buffer.f_bavail));
    obj->Set(Nan::New("files").ToLocalChecked(), 
            Nan::New<Number>(buffer.f_files));
    obj->Set(Nan::New("ffree").ToLocalChecked(), 
            Nan::New<Number>(buffer.f_ffree));
    obj->Set(Nan::New("favail").ToLocalChecked(), 
            Nan::New<Number>(buffer.f_favail));
    obj->Set(Nan::New("flag").ToLocalChecked(), 
            Nan::New<Number>(buffer.f_flag));
    obj->Set(Nan::New("namemax").ToLocalChecked(), 
            Nan::New<Number>(buffer.f_namemax));
    info.GetReturnValue().Set(obj);
}




