-- help
function console.cmd_help()
	print("List of available commands:")
	print("----------------------------------------")
	for k,v in pairs(console.Commands) do
		print(k)
	end
	print("----------------------------------------")
end
console.RegisterCommand("help", console.cmd_help)

-- Load Addon
function console.cmd_load_addon(name)
	-- Syntax
	if name == nil then
		print("Syntax: load_addon/reload_addon [name]")
		return
	end
	
	-- Load
	print("Loading ", name, "...")
	addon.Load(name)
	print("")
end
console.RegisterCommand("reload_addon", console.cmd_load_addon)
console.RegisterCommand("load_addon", console.cmd_load_addon)

-- Unload Addon
function console.cmd_unload_addon(name)
	-- Syntax
	if name == nil then
		print("Syntax: unload_addon [name]")
		return
	end
	
	-- Unload
	print("Unloading ", name, "...")
	addon.Unload(name)
	print("")
end
console.RegisterCommand("unload_addon", console.cmd_unload_addon)

-- Immediate execute lua code
function console.cmd_exec(expression)
	-- Syntax
	if type(expression) ~= "string" then
		print("Syntax: exec \"[lua expression]\"")
		return
	end

	functor, e = loadstring(expression)
	if functor then
		functor()
	else
		-- Display the error
		print("Error running exec:")
		print(e)
	end
end
console.RegisterCommand("exec", console.cmd_exec)