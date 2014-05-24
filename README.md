Nsutil.js
===
Node.js system utilities

[![NPM](https://nodei.co/npm/nsutil.png)](https://nodei.co/npm/nsutil/)

###Summary

* a fork of [psutil](https://code.google.com/p/psutil/), rebuilt with Node.js
* support OSX & Linux

###Install

    npm install nsutil

###Prebuilt binaries (node v0.10.28)

    OSX x86_64
    Linux x86_64

###Rebuild (if you need)

```bash
node-gyp configure build
```

###Usage

```js
var ns = require('nsutil')
```

###APIs

####system methods

ns.virtualMemory()
```js
 // OSX
 { total:    4294967296,
   active:   1476833280,
   inactive: 926130176,
   wire:     1203470336,
   free:     237256704,
   avail:    1163386880,
   used:     3606433792 }

 // Linux
 { total:    383238144,
   avail:    315265024,
   inactive: 71880704,
   used:     206503936,
   free:     176734208,
   active:   66637824,
   buffers:  25927680,
   cached:   112603136 }
```

ns.swapMemory()
```js
 { total: 1073741824,
   used:  6815744,
   free:  1066926080,
   sin:   2724483072,
   sout:  20860928 }    
``` 

ns.cpuTimes()
```js    
 { user: 40.76, nice: 118.53, system: 683.01, idle: 287470.94 }
``` 

ns.perCpuTimes()
```js
 [ { user: 174.18, nice: 0, sys: 123.64, idle: 1411.73 },
   { user: 68.05,  nice: 0, sys: 42.15,  idle: 1599.30 },
   { user: 129.05, nice: 0, sys: 62.55,  idle: 1517.90 },
   { user: 58.15,  nice: 0, sys: 28.77,  idle: 1622.58 } ] 
``` 

ns.cpuCountLogical()
```js
 4
```

ns.cpuCountPhys()
```js
 2
```

ns.bootTime()
```js
 1400543744000 // timestamp ms
```

ns.diskPartitions()
```js
 [ { device: '/dev/disk0s2',
     mount_point: '/',
     fs_type: 'hfs',
     options: 'rw,local,rootfs,dovolfs,journaled,multilabel' },
   { device: 'devfs',
     mount_point: '/dev',
     fs_type: 'devfs',
     options: 'rw,local,dontbrowse,multilabel' },
     ...] 
```

ns.users()
```js
 [
  {"username":"Dx.Yang", "tty":"console", "host":"", "startTime":1400548608},
  {"username":"Dx.Yang", "tty":"ttys000", "host":"", "startTime":1400548608},
  {"username":"Dx.Yang", "tty":"ttys001", "host":"", "startTime":1400548608}
 ]
```

ns.pids()
```js
 [6652,6651,6640,6639,6638,6633,6632,6615,6606...]
```

ns.netConnections()
```js
 [ { fd: 22,
     family: 'AF_INET',
     type: 'SOCK_STREAM',
     laddr: ['X.X.X.X', XXXX],
     raddr: ['X.X.X.X', XXXX],
     state: 'ESTABLISHED' },
    ...]
```

ns.netIOCounters()
```js
 { bridge0: 
   { obytes: 684,
     ibytes: 0,
     opkts: 2,
     ipkts: 0,
     oerrs: 0,
     ierrs: 0,
     iqdrops: 0 },
  en0: 
   { obytes: 160304770,
     ibytes: 2578607670,
     opkts: 1614175,
     ipkts: 2421909,
     oerrs: 0,
     ierrs: 0,
     iqdrops: 0 },
  ...}
```

ns.diskIOCounters()
```js
 { disk0: 
   { reads: 1170484,
     writes: 668337,
     read_bytes: 18236701696,
     write_bytes: 21262711296,
     read_time: 825561,
     write_time: 540807 },
   disk1:
   { reads: 11704,
     writes: 6683,
     read_bytes: 182367016,
     write_bytes: 212627112,
     read_time: 8255,
     write_time: 5408 }
   ...} 
```


#####Class Process

var proc = ns.Process(pid)

proc.name()
```js
 'node'
```

proc.exe()
```js
 '/usr/local/bin/node'
```

proc.cmdline()
```js
 [ 'node',
   '/usr/local/lib/node_modules/mocha/bin/_mocha',
   'test_osx.js',
   '-R',
   'spec' ]
```

proc.ppid()
```js
 6651  //parent process id    
```

proc.cwd()
```js
 '/Users/node_modules/nsutil/test'
```

proc.uids()
```js
 { real: 501, effective: 501, saved: 501 }
```

proc.gids()
```js
 { real: 20, effective: 20, saved: 20 }
```

proc.terminal()
```js
 /dev/ttys004
```

proc.memoryInfo()   
```js
 { rss: 18440192, vms: 3119169536, faults: 19517440, pageins: 0 }
```

proc.cpuTimes()
```js
 { user: 0.139774113, sys: 0.027113125 }    // s
```

proc.createTime()
```js
 1400565545000 // timestamp ms
```

proc.numCtxSwitches()
```js    
 // OSX
 271
 
 // Linux
 { voluntary_ctxt_switches: 32, nonvoluntary_ctxt_switches: 4 }
```

proc.numThreads()
```js
 4
```

proc.openFiles()
```js
 [ { path: '/dev/ttys004', fd: 0 },
   { path: '/dev/ttys004', fd: 1 },
   { path: '/dev/ttys004', fd: 2 },
  ... ]
```

proc.connections('inet')    **// default is 'all'***
```js
 [ { fd: 22,
     family: 'AF_INET',
     type: 'SOCK_STREAM',
     laddr: ['X.X.X.X', XXXX],
     raddr: ['X.X.X.X', XXXX],
     state: 'ESTABLISHED' },
    ...] 
```

proc.numFds()
```js
 12
```

proc.getNice()
```js
 0
```

proc.setNice(niceValue)

proc.status()
```js
 running
```

proc.threads()
```js
 [ { idx: 1, 
     user: 0.14695000648498535, 
     sys: 0.02574799954891205 },
   { idx: 2,
     user: 0.00007100000220816582,
     sys: 0.00008600000001024455 },
   { idx: 3,
     user: 0.00002499999936844688,
     sys: 0.00008499999967170879 },
   { idx: 4,
     user: 0.0006169999833218753,
     sys: 0.0019920000340789557 } ]
```

proc.memMaps()
```js
 // OSX
 [
    {
        "pmmap_ext" : "0000000100000000-0000000100617000",
        "addr_perms" : "r-x/rwx",
        "path":"/usr/local/bin/node",
        "rss" : 45056,
        "private" : 0,
        "swapped" : 0,
        "dirtied" : 0,
        "ref_count" : 7,
        "shadow_depth" : 1
    },
    ...]

 // Linux
 [
    {  
        "pmmap_ext": "7f1517342000-7f151734e000",
        "addr_perms": "r-xp",
        "path": "/lib/x86_64-linux-gnu/libnss_files-2.17.so",
        "Size": 49152,
        "Rss": 0, 
        "Pss": 0, 
        "Shared_Clean": 0, 
        "Shared_Dirty": 0, 
        "Private_Clean": 0,
        "Private_Dirty": 0,
        "Referenced": 0,
        "Anonymous": 0,
        "AnonHugePages": 0,
        "Swap": 0,
        "KernelPageSize": 4096,
        "MMUPageSize": 4096,
        "Locked": 0
    },
    ...]

```

proc.ioCounters()   **// Linux only**
```js
 { rcount: 20474, wcount: 14600, rbytes: 2109440, wbytes: 8192 }
```




