test_entity = {
	x = 0.0,
	y = 0.0,
	z = 0.0,
	dir = 0,
	length = 0
}

function test_entity:new(o)
	o = o or {}
	self.__index = self;
	setmetatable(o, self)
	return o
end

function test_entity.update(self, delta)
	-- show_msg("update, x = " .. self.x .. ", y = " .. self.y .. ", z = " .. self.x)
	if self.dir == 0 then
		self.x = self.x + delta * 60
	elseif self.dir == 1 then
		self.z = self.z + delta * 60
	elseif self.dir == 2 then
		self.x = self.x - delta * 60
	elseif self.dir == 3 then
		self.z = self.z - delta * 60
	end

	self.length = self.length + 1
	if self.length == 1000 then
		self.dir = (self.dir + 1) % 4
		self.length = 0
	end
end