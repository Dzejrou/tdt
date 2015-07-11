test_entity = {
	x = 0.0,
	y = 0.0,
	z = 0.0,
	dir = 0,
	lenght = 0
}

function test_entity:new(o)
	o = o or {}
	self.__index = self;
	setmetatable(o, self)
	return o
end

function test_entity:update(delta)
	if dir == 0 then
		x = x + delta * 0.001
	elseif dir == 1 then
		z = z + delta * 0.001	
	elseif dir == 2 then
		x = x - delta * 0.001
	elseif dir == 3 then
		z = z - delta * 0.001
	end

	length = length + 1
	if length == 1000 then
		dir = (dir + 1) % 4
		length = 0
	end
end