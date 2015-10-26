#include "nsutil_linux_funcs.h"

using namespace v8;
using namespace std;

#if SUTIL_HAVE_IOPRIO

NAN_METHOD(nsutil_pid_exists)
{
    Nan::HandleScope() scope;
    if (info.Length() == 0) {
        Nan::ThrowTypeError("Wrong number of arguments");
        info.GetReturnValue().Set(Nan::Undefined());
    }
    if (!info[0]->IsNumber()) {
        Nan::ThrowTypeError("Wrong arguments");
        info.GetReturnValue().Set(Nan::Undefined());
    }
    int32_t pid = info[0]->Int32Value();
    info.GetReturnValue().Set(Nan::New<Boolean>(sutil_pid_exists(pid)));
}

NAN_METHOD(nsutil_proc_ioprio_get) 
{
    Nan::HandleScope() scope;
    if (info.Length() == 0) {
        Nan::ThrowTypeError("Wrong number of arguments");
        info.GetReturnValue().Set(Nan::Undefined());
    }
    if (!info[0]->IsNumber()) {
        Nan::ThrowTypeError("Wrong arguments");
        info.GetReturnValue().Set(Nan::Undefined());
    }
    int32_t pid = info[0]->Int32Value();
    int *proc_ioprio = new int[2];
    if (sutil_proc_ioprio_get(pid, proc_ioprio) == -1) {
        info.GetReturnValue().Set(Nan::Undefined());
    }
    Local<Object> obj = Nan::New<Object>();
    obj->Set(Nan::New("class").ToLocalChecked(), Nan::New<Integer>(proc_ioprio[0]));
    obj->Set(Nan::New("data").ToLocalChecked(), Nan::New<Integer>(proc_ioprio[1]));

    delete[] proc_ioprio;
    info.GetReturnValue().Set(obj);
}

NAN_METHOD(nsutil_proc_ioprio_set) 
{
    Nan::HandleScope() scope;
    if (info.Length() != 3) {
        Nan::ThrowTypeError("Wrong number of arguments");
        info.GetReturnValue().Set(Nan::Undefined());
    }
    if (!info[0]->IsNumber() || !info[1]->IsNumber() || !info[2]->IsNumber()) {
        Nan::ThrowTypeError("Wrong arguments");
        info.GetReturnValue().Set(Nan::Undefined());
    }

    int32_t pid = info[0]->Int32Value();
    int io_class = info[1]->IntegerValue();
    int io_data = info[2]->IntegerValue();

    int re = sutil_proc_ioprio_set(pid, io_class, io_data);
    info.GetReturnValue().Set(Nan::New<Integer>(re));
}

#endif


#if SUTIL_HAVE_PRLIMIT

//XXX: TODO: get set
NAN_METHOD(nsutil_linux_prlimit) 
{
    Nan::HandleScope() scope;
    info.GetReturnValue().Set(Nan::Undefined());
}

#endif


NAN_METHOD(nsutil_disk_partitions)
{
    Nan::HandleScope() scope;

    vector<vector<string>> devlist;

    if (sutil_disk_partitions(devlist) == -1) {
        info.GetReturnValue().Set(Nan::Undefined());
    }
    
    Local<Array> arr = Nan::New<Array>(devlist.size());

    int i = 0;
    Local<Object> obj = Nan::New<Object>();
    for (auto &dev : devlist) {
        obj->Set(Nan::New("device").ToLocalChecked(),
                Nan::New(dev[0].c_str().ToLocalChecked()));
        obj->Set(Nan::New("mountpoint").ToLocalChecked(),
                Nan::New(dev[1].c_str().ToLocalChecked()));
        obj->Set(Nan::New("fstype").ToLocalChecked(),
                Nan::New(dev[2].c_str().ToLocalChecked()));
        obj->Set(Nan::New("opts").ToLocalChecked(),
                Nan::New(dev[3].c_str().ToLocalChecked()));
        arr->Set(i, obj->Clone());
        i++;
    }


    info.GetReturnValue().Set(arr);
}

//int
//sutil_linux_sysinfo(uint64_t* &info)
NAN_METHOD(nsutil_sysinfo)
{
    Nan::HandleScope() scope;
    
    uint64_t* info = new uint64_t[6]; 

    if (sutil_linux_sysinfo(info) == -1) {
        info.GetReturnValue().Set(Nan::Undefined());
    }

    Local<Object> obj = Nan::New<Object>();

    obj->Set(Nan::New("total").ToLocalChecked(), 
            Nan::New<Number>(info[0]));
    obj->Set(Nan::New("free").ToLocalChecked(), 
            Nan::New<Number>(info[1]));
    obj->Set(Nan::New("buffer").ToLocalChecked(), 
            Nan::New<Number>(info[2]));
    obj->Set(Nan::New("shared").ToLocalChecked(), 
            Nan::New<Number>(info[3]));
    obj->Set(Nan::New("swap_total").ToLocalChecked(), 
            Nan::New<Number>(info[4]));
    obj->Set(Nan::New("swap_free").ToLocalChecked(), 
            Nan::New<Number>(info[5]));

    delete[] info;
    info.GetReturnValue().Set(obj);
}

//int
//sutil_proc_cpu_affinity_get(const int32_t pid, uint32_t &mask)
NAN_METHOD(nsutil_proc_cpu_affinity_get)
{
    Nan::HandleScope() scope;
    if (info.Length() == 0) {
        Nan::ThrowTypeError("Wrong number of arguments");
        info.GetReturnValue().Set(Nan::Undefined());
    }
    if (!info[0]->IsNumber()) {
        Nan::ThrowTypeError("Wrong arguments");
        info.GetReturnValue().Set(Nan::Undefined());
    }
    int32_t pid = info[0]->Int32Value();
    uint32_t mask;
    
    if (sutil_proc_cpu_affinity_get(pid, mask) == -1) {
        info.GetReturnValue().Set(Nan::Undefined());
    }

    info.GetReturnValue().Set(Nan::New<Number>(mask));
}

//XXX
//int
//sutil_proc_cpu_affinity_set(const int32_t &pid, vector<int32_t> &cpu_set_list)
/*
NAN_METHOD(nsutil_proc_cpu_affinity_set) 
{
    Nan::HandleScope(;

    if (info.Length() != 2) {
        Nan::ThrowTypeError("Wrong number of arguments");
        info.GetReturnValue().Set(Nan::Undefined());
    }
    if (!info[0]->IsNumber() || !info[1]->IsArray()) {
        Nan::ThrowTypeError("Wrong arguments");
        info.GetReturnValue().Set(Nan::Undefined());
    }

    int32_t pid = info[0]->Int32Value();


    //TODO

    info.GetReturnValue().Set(Nan::Undefined());

}
*/




//int
//sutil_users(vector<sutil_user_info> &user_list)
NAN_METHOD(nsutil_users)
{
    Nan::HandleScope() scope;

    vector<sutil_user_info> user_list;

    if (sutil_users(user_list) == -1) {
        info.GetReturnValue().Set(Nan::Undefined());
    }
    
    Local<Array> arr = Nan::New<Array>(user_list.size());
    Local<Object> obj = Nan::New<Object>();

    int i = 0;
    for (auto &u : user_list) {
        obj->Set(Nan::New("username").ToLocalChecked(), Nan::New(u.username.c_str().ToLocalChecked()));
        obj->Set(Nan::New("tty").ToLocalChecked(), Nan::New(u.tty.c_str().ToLocalChecked()));
        obj->Set(Nan::New("host").ToLocalChecked(), Nan::New(u.host.c_str().ToLocalChecked()));
        obj->Set(Nan::New("start_time").ToLocalChecked(), Nan::New<Number>(u.start_time));
        obj->Set(Nan::New("user_proc").ToLocalChecked(), Nan::New<Boolean>(u.user_proc));
        arr->Set(i, obj->Clone());
        i++;
    }

    info.GetReturnValue().Set(arr);
}



// sysconf
NAN_METHOD(nsutil_sysconf) 
{
    Nan::HandleScope() scope;
    if (info.Length() == 0) {
        Nan::ThrowTypeError("Wrong number of arguments");
        info.GetReturnValue().Set(Nan::Undefined());
    }
    if (!info[0]->IsString()) {
        Nan::ThrowTypeError("Wrong arguments");
        info.GetReturnValue().Set(Nan::Undefined());
    }
    String::Utf8Value str(info[0]->ToString());
    string which = *str;
    
    int ret = sutil_sysconf(which);
    info.GetReturnValue().Set(Nan::New<Number>(ret));
}









