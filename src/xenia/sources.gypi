# Copyright 2013 Ben Vanik. All Rights Reserved.
{
  'sources': [
    'common.h',
    'core.h',
    'debug_agent.cc',
    'debug_agent.h',
    'emulator.cc',
    'emulator.h',
    'export_resolver.cc',
    'export_resolver.h',
    'logging.h',
    'memory.cc',
    'memory.h',
    'profiling.cc',
    'profiling.h',
    'xbox.h',
  ],

  'includes': [
    'apu/sources.gypi',
    'core/sources.gypi',
    'cpu/sources.gypi',
    'gpu/sources.gypi',
    'hid/sources.gypi',
    'kernel/sources.gypi',
    'ui/sources.gypi',
  ],
}
