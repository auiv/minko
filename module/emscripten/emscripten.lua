premake.extensions.emscripten = {}

local emscripten = premake.extensions.emscripten
local project = premake.project
local api = premake.api
local make = premake.make
local cpp = premake.make.cpp
local project = premake.project
local config = premake.config
local fileconfig = premake.fileconfig

api.addAllowed("system", { "emscripten" })

local EMSCRIPTEN

if os.getenv('EMSCRIPTEN') then
	EMSCRIPTEN = os.getenv('EMSCRIPTEN');
elseif os.getenv('EMSCRIPTEN_HOME') then
	EMSCRIPTEN = os.getenv('EMSCRIPTEN_HOME');
else
	print(color.fg.yellow .. 'You must define the environment variable EMSCRIPTEN to be able to target HTML5.' .. color.reset)
	EMSCRIPTEN = ''
end

if os.is('windows') then
	table.inject(premake.tools.gcc, 'tools.emscripten', {
		cc = '"' .. EMSCRIPTEN .. '\\emcc.bat"',
		cxx = 'call "%MINKO_HOME%\\module\\emscripten\\em++.bat"',
		pkg = 'python "%MINKO_HOME%\\module\\emscripten\\empkg.py"',
		ar = '"' .. EMSCRIPTEN .. '\\emar.bat"'
	})
else
	table.inject(premake.tools.gcc, 'tools.emscripten', {
		cc = path.cygpath(MINKO_HOME) .. '/module/emscripten/emcc.sh',
		cxx = path.cygpath(MINKO_HOME) .. '/module/emscripten/em++.sh',
		pkg = path.cygpath(MINKO_HOME) .. '/module/emscripten/empkg.py',
		ar = path.cygpath(MINKO_HOME) .. '/module/emscripten/emar.sh'
	})
end

table.inject(premake.tools.gcc, 'cppflags.system.emscripten', {
	"-MMD", "-MP",
	"-DEMSCRIPTEN"
})

table.inject(premake.tools.gcc, 'cxxflags.system.emscripten', {
	'"-std=c++11"',
})
