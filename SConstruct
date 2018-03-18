import os
env = Environment(ENV = os.environ)

env.Append(LIBS=["png"])
env.Append(CXXFLAGS=["-std=c++11","-g","-Wall","-O3"])
env.Append(LINKFLAGS=[])

env_nogl = env.Clone()
env_nogl.Append(CXXFLAGS=["-DNO_OPENGL"])

if env['PLATFORM'] == 'darwin':
    env.Append(CXXFLAGS=["-Wno-deprecated-declarations"])
    env.Append(LINKFLAGS=["-framework", "OpenGL", "-framework", "GLUT"])
else:
    env.Append(LIBS=["glut","GL","X11"])


sources = ['src/core/application.cpp', 'src/core/main.cpp', 'src/model/bowl.cpp', 'src/model/bowlingMachine.cpp', 'src/model/model.cpp', 'src/model/pin.cpp', 'src/model/pinSet.cpp', 'src/model/place.cpp', 'src/utils/movingObject.cpp', 'src/utils/texturizableObject.cpp', 'src/view/camera.cpp', 'src/view/image.cpp', 'src/view/view.cpp', 'src/controller/controller.cpp']
# print Glob('core/*.cpp')
env.Program("bowling_game", sources)
