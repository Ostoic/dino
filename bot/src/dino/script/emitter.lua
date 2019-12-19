R"(
dino = CreateFrame('frame')
dino.events = {}
dino.internals = {}

function dino.is_glue()
	if not print then
		return true
	else
		return false
	end
end

function dino.lua(script)
	dino_action_data = script
	dino_action = 'lua.execute'
end

function dino.command(args)
	dino_action_data = args
	dino_action = 'dino.command'
end

function dino.internals.register(name, event, fn)
	print('dino.internals.register: ' .. event .. ', ' .. name)
	if not dino.events[event] then
		dino:RegisterEvent(event)
		dino.events[event] = {}
	end

	dino.events[event][name] = fn
end

function dino.internals.unregister(name, event)
	print('dino.unregister: ' .. event .. ', ' .. name)
	if not dino.events[event] then dino.events[event] = {} end
	dino.events[event][name] = nil

	if #dino.events[event] == 0 then
		dino:UnregisterEvent(event)
	end
end

dino:SetScript('OnEvent', function(self, event, ...)
	local arg = {...}
	fns = dino.events[event]
	if fns then
		for name, fn in pairs(fns) do
			fn(json.stringify({event = event, args = arg}))
		end
	end
end)

if SlashCmdList then
	SLASH_DINO1 = '/dino'
	SlashCmdList['DINO'] = dino.command
	
	SLASH_DRUN1 = '/drun'
	SlashCmdList['DRUN'] = dino.lua
end
)";