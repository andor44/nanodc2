
import os
import commands
import string

EnsureSConsVersion(0, 96)

def CheckPKGConfig(context): 
     context.Message('Checking for pkg-config... ') 
     ret = context.TryAction('pkg-config --version')[0] 
     context.Result(ret)
     return ret 
 
def CheckPKG(context, name): 
     context.Message('Checking for %s... ' % name) 
     ret = context.TryAction('pkg-config --exists \'%s\'' % name)[0] 
     context.Result(ret) 
     return ret 

def CheckCXXVersion(context, name, major, minor):
    context.Message('Checking for %s >= %d.%d...' % (name, major, minor))

    ret = commands.getoutput('%s -dumpversion' % name)
    retval = 0
    if(ret.find('not found') == -1):
        if(string.atoi(ret[0]) == major and string.atoi(ret[2]) >= minor):
            retval = 1
        elif(string.atoi(ret[0]) > major):
            retval = 1
                
    context.Result(retval)
    return retval

env = Environment(ENV = os.environ)

conf = Configure(env,
    custom_tests = {
        'CheckPKGConfig' : CheckPKGConfig, 
        'CheckPKG' : CheckPKG,
        'CheckCXXVersion' : CheckCXXVersion
    }) 

if os.environ.has_key('CXX'):
     env['CXX'] = os.environ['CXX']

if os.environ.has_key('CXXFLAGS'):
     env['CXXFLAGS'] = os.environ['CXXFLAGS'].split()

# Dependencies
if not conf.CheckCXXVersion(env['CXX'], 4, 0):
     print 'Compiler version check failed. g++ 4.0 or later is needed'
     Exit(1)

# Add support for compiler caches to speed-up compilation.
if conf.TryAction(Action('distcc'))[0]:
    env.Prepend(CXX = 'distcc ')
    print 'Enabling distcc...'

if conf.TryAction(Action('ccache'))[0]:
    env.Prepend(CXX = 'ccache ')
    print 'Enabling ccache...'

if not conf.CheckPKGConfig(): 
     print 'pkg-config not found.' 
     Exit(1) 

if not conf.CheckCXXHeader('tr1/functional'):
    print 'Did not find the header tr1/functional (need CGG 4.0 or later)'
    Exit(1)

if not conf.CheckLibWithHeader('ncursesw', 'ncurses.h', 'c++'):
    print 'Did not find the ncursesw library'
    print 'Can\'t live without it, exiting'
    print 'Note: You might have the lib but not the headers (install dev-package)'
    Exit(1)

if not conf.CheckLibWithHeader('pthread', 'pthread.h', 'c++'):
    print 'Did not find the pthread library, exiting!'
    print 'Note: You might have the lib but not the headers'
    Exit(1)

if not conf.CheckLibWithHeader('z', 'zlib.h', 'c++'):
    print 'Did not find the z library (gzip/z compression)'
    print 'Can\'t live without it, exiting'
    print 'Note: You might have the lib but not the headers'
    Exit(1)

if not conf.CheckLibWithHeader('bz2', 'bzlib.h', 'c++'):
    print 'Did not find the bz2 library (bz2 compression)'
    print 'Can\'t live without it, exiting'
    print 'Note: You might have the lib but not the headers'
    Exit(1)

if not conf.CheckPKG('glib-2.0'):
    print 'Did not find the glib-2.0 library'
    print 'Can\'t live without it, exiting'
    print 'Note: You might have the lib but not the development package (libglib2.0-dev)'
    Exit(1)

#if not conf.CheckPKG('sigc++-2.0'):
#    print 'Did not find the sigc++-2.0 library'
#    print 'Can\'t live without it, exiting'
#    Exit(1)

if not conf.CheckLibWithHeader('boost_signals', 'boost/signals.hpp', 'c++'):
    print 'Did not find the boost_signals library, exiting!'
    print 'Note: You might have the lib but not the headers'
    Exit(1)

if not conf.CheckLibWithHeader('boost_thread', 'boost/thread.hpp', 'c++'):
    print 'Did not find the boost_thread library, exiting!'
    print 'Note: You might have the lib but not the headers'
    Exit(1)

if not conf.CheckLibWithHeader('ssl', 'openssl/ssl.h', 'c++'):
    print '\tOpenSSL library (libssl) not found'
    print '\tNote: You might have the lib but not the headers'
    Exit(1)

if not conf.CheckFunc('backtrace'):
    conf.env.Prepend(CXXFLAGS = '-DUSE_STACKTRACE=0')
else:
    conf.env.Prepend(CXXFLAGS = '-DUSE_STACKTRACE=1')

env = conf.Finish()
env.Append(CXXFLAGS = ['-I.', '-ansi', '-Wall', '-std=c++0x'])
#env.Append(CXXFLAGS = commands.getoutput('pkg-config sigc++-2.0 --cflags').split())
env.Append(CXXFLAGS = commands.getoutput('pkg-config glib-2.0 --cflags').split())
#env.Append(_LIBFLAGS = ' ' + commands.getoutput('pkg-config sigc++-2.0 --libs'))
env.Append(_LIBFLAGS = ' ' + commands.getoutput('pkg-config glib-2.0 --libs'))

release = ARGUMENTS.get('release', 0)
debug = ARGUMENTS.get('debug', 0)

if int(release):
    env.Append(CXXFLAGS = '-O2')
elif int(debug):
    env.Append(CXXFLAGS = ['-g', '-rdynamic'])
else:
    env.Append(CXXFLAGS = '-rdynamic')

build = env.Program('nanodc', [
    SConscript('client/SConscript', exports='env', variant_dir='build/client', duplicate=0),
    SConscript('core/SConscript', exports='env', variant_dir='build/core', duplicate=0),
    SConscript('input/SConscript', exports='env', variant_dir='build/input', duplicate=0), 
    SConscript('utils/SConscript', exports='env', variant_dir='build/utils', duplicate=0),
    SConscript('ui/SConscript', exports='env', variant_dir='build/ui', duplicate=0),
    SConscript('display/SConscript', exports='env', variant_dir='build/display', duplicate=0),
    SConscript('modules/SConscript', exports='env', variant_dir='build/commands', duplicate=0),
])

Default(build)

