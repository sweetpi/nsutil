#ifndef BUILDING_NODE_EXTENSION
#define BUILDING_NODE_EXTENSION
#endif
#include <node.h>
#include <nan.h>
#include <v8.h>
#include "nsutil_linux_funcs.h"

using v8::FunctionTemplate;
using v8::String;

void Init(v8::Handle<v8::Object> exports) {
#if SUTIL_HAVE_IOPRIO
    exports->Set(Nan::New<String>("nsutil_proc_ioprio_get").ToLocalChecked(), 
            Nan::New<FunctionTemplate>(nsutil_proc_ioprio_get)->GetFunction());
    exports->Set(Nan::New<String>("nsutil_proc_ioprio_set").ToLocalChecked(), 
            Nan::New<FunctionTemplate>(nsutil_proc_ioprio_set)->GetFunction());
#endif

    exports->Set(Nan::New<String>("nsutil_disk_partitions").ToLocalChecked(), 
            Nan::New<FunctionTemplate>(nsutil_disk_partitions)->GetFunction());

    exports->Set(Nan::New<String>("nsutil_sysinfo").ToLocalChecked(), 
            Nan::New<FunctionTemplate>(nsutil_sysinfo)->GetFunction());

    exports->Set(Nan::New<String>("nsutil_proc_cpu_affinity_get").ToLocalChecked(), 
            Nan::New<FunctionTemplate>(nsutil_proc_cpu_affinity_get)->GetFunction());

    exports->Set(Nan::New<String>("nsutil_users").ToLocalChecked(), 
            Nan::New<FunctionTemplate>(nsutil_users)->GetFunction());

    exports->Set(Nan::New<String>("nsutil_pid_exists").ToLocalChecked(), 
            Nan::New<FunctionTemplate>(nsutil_pid_exists)->GetFunction());

    exports->Set(Nan::New<String>("nsutil_sysconf").ToLocalChecked(), 
            Nan::New<FunctionTemplate>(nsutil_sysconf)->GetFunction());

    /*
    exports->Set(Nan::New<String>("nsutil_").ToLocalChecked(), 
            Nan::New<FunctionTemplate>(nsutil_)->GetFunction());

            */

}

NODE_MODULE(nsutil_linux, Init);
