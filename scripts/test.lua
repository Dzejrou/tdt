programmer = {
	name = "Dzejrou",
	age = 23,
	history = {
		high_school = "Omska",
		university = "MMF UK"
	}
}

function sum(...)
	local s = 0
	for _, v in ipairs{...} do
		s = s + v
	end
	return s
end