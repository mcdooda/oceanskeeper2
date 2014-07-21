local math = math
local PI = math.pi

-- ship missiles

do
	-- ship missile 1
	
	local numMissiles = 6
	local radius = 25
	
	newMissileModel{
		name        = "ShipMissile1",
		damage      = 100,
		firePeriod  = 0.1,
		numMissiles = numMissiles,
		angle       = 0,
		speed       = 1000,
		laser       = true,
		texture     = "units/ship/blue/laser3.png",
		texture2    = "units/ship/blue/startlaser3.png",
		texture3    = "units/ship/blue/endlaser3.png",
		sample      = "missiles/missile1.ogg",
		pop         = function(m, _, i)
			local data = Entity.getExtraData(m)
			data.a = i / numMissiles * PI * 2
		end,
		ai          = function(m)
			local shooter = Entity.getById(Entity.getMissileShooterId(m))
			if shooter then
				local sX, sY = Entity.getPosition(shooter)
				local data = Entity.getExtraData(m)
				
				local t = getTime() * 10 + data.a
				local x = math.cos(t) * radius
				local y = -5
				local z = Entity.getZ(shooter) + math.sin(t) * radius
				local angle = Entity.getAngle(shooter)

				
				local a = angle + PI / 2
				local lX = math.cos(a) * x - math.sin(a) * y
				local lY = math.sin(a) * x + math.cos(a) * y
				
				Entity.setPosition(m, sX + lX, sY + lY)
				Entity.setZ(m, z)
				Entity.setAngle(m, angle + math.cos(t) / 10)
			end
		end
	}
	
end

do
	-- ship missile 2
	
	newMissileModel{
		name        = "ShipMissile2",
		damage      = 4,
		firePeriod  = 0.05,
		numMissiles = 2,
		angle       = 0,
		speed       = 1600,
		texture     = "units/ship/blue/missile2.png",
		sample      = "missiles/missile1.ogg"
	}
	
end

do
	-- ship missile 3
	
	newMissileModel{
		name        = "ShipMissile3",
		damage      = 3,
		firePeriod  = 0.07,
		numMissiles = 5,
		angle       = PI / 24,
		speed       = 1400,
		texture     = "units/ship/blue/missile3.png",
		sample      = "missiles/missile1.ogg"
	}
	
end

do
	-- ship missile 4
	
	newMissileModel{
		name        = "ShipMissile4",
		damage      = 3,
		firePeriod  = 0.08,
		numMissiles = 8,
		angle       = PI / 4,
		speed       = 0,
		texture     = "units/ship/blue/missile4.png",
		sample      = "missiles/missile1.ogg",
		pop         = function(m)
			Entity.getExtraData(m).popTime = getTime()
		end,
		ai          = function(m)
			local data = Entity.getExtraData(m)
			local age = getTime() - data.popTime
			Entity.setSpeed(m, (age + 1) * (age + 1) * 600 + 900)
			if not data.angleSet then
				local lastAngle = Entity.getAngle(m)
				if lastAngle < -PI / 2 then
					Entity.turn(m, 2)
					local angle = Entity.getAngle(m)
					if angle >= -PI / 2 then
						Entity.setAngle(m, -PI / 2)
						data.angleSet = true
					end
				else
					Entity.turn(m, -2)
					local angle = Entity.getAngle(m)
					if angle <= -PI / 2 then
						Entity.setAngle(m, -PI / 2)
						data.angleSet = true
					end
				end
			end
		end
	}
	
end

do
	-- ship missile 5
	
	newMissileModel{
		name        = "ShipMissile5",
		damage      = 4,
		firePeriod  = 0.06,
		numMissiles = 4,
		angle       = PI / 32,
		speed       = 1500,
		texture     = "units/ship/blue/missile5.png",
		sample      = "missiles/missile1.ogg",
		pop         = function(m)
			local mX, mY = Entity.getPosition(m)
			local mAngle = Entity.getAngle(m)
			popMissile{
				model    = "ShipMissile5bis",
				position = {mX - 30, mY},
				angle    = mAngle - PI / 24,
				side     = ALLY,
				params   = 1
			}
			popMissile{
				model    = "ShipMissile5bis",
				position = {mX + 30, mY},
				angle    = mAngle + PI / 24,
				side     = ALLY,
				params   = -1
			}
		end
	}
	
	newMissileModel{
		name        = "ShipMissile5bis",
		damage      = 3,
		firePeriod  = 1,
		numMissiles = 1,
		angle       = 0,
		speed       = 1500,
		texture     = "units/ship/blue/missile5.png",
		sample      = "missiles/missile1.ogg",
		pop         = function(m, turn)
			Entity.getExtraData(m).turn = turn
		end,
		ai          = function(m)
			Entity.turn(m, Entity.getExtraData(m).turn / 2)
		end
	}
	
end

do
	-- ship missile 6
	
	newMissileModel{
		name        = "ShipMissile6",
		damage      = 15,
		firePeriod  = 0.1,
		numMissiles = 20,
		angle       = 3 * PI,
		speed       = 1000,
		texture     = "units/ship/blue/missile6.png",
		sample      = "missiles/missile1.ogg",
		pop         = function(m)
			Entity.getExtraData(m).popTime = getTime()
		end,
		ai          = function(m)
			local data = Entity.getExtraData(m)
			local age = getTime() - data.popTime
			if not data.angleSet then
				local lastAngle = Entity.getAngle(m)
				if lastAngle < -PI / 2 then
					Entity.turn(m, 30)
					local angle = Entity.getAngle(m)
					if angle >= -PI / 2 then
						Entity.setAngle(m, -PI / 2)
						data.angleSet = true
						Entity.setSpeed(m, 1700)
					end
				else
					Entity.turn(m, -30)
					local angle = Entity.getAngle(m)
					if angle <= -PI / 2 then
						Entity.setAngle(m, -PI / 2)
						data.angleSet = true
						Entity.setSpeed(m, 1700)
					end
				end
			end
		end
	}
	
end

do
	-- ship missile 7
	
	newMissileModel{
		name        = "ShipMissile7",
		damage      = 30,
		firePeriod  = 0.02,
		numMissiles = 10,
		angle       = 1,
		speed       = 500,
		texture     = "units/ship/blue/missile7.png",
		sample      = "missiles/missile1.ogg",
		pop         = function(m)
			local angle = math.random() * PI * 2
			local sX, sY = Entity.getPosition(getShip())
			Entity.setPosition(m, sX + math.cos(angle) * 40, sY + math.sin(angle) * 40)
			Entity.setAngle(m, angle)
			Entity.getExtraData(m).popTime = getTime()
		end,
		ai          = function(m)
			Entity.setSpeed(m, 400 + (getTime() - Entity.getExtraData(m).popTime) ^ 3 * 1000)
		end
	}
	
end

do
	-- ship special 1
	
	newMissileModel{
		name        = "ShipSpecial1",
		damage      = 5,
		firePeriod  = 1,
		numMissiles = 30,
		angle       = 0.02,
		speed       = 800,
		texture     = "units/ship/blue/special1.png",
		sample      = "missiles/special1.ogg",
		pop         = function(m)
			local ship = getShip()
			Effect.add("blank.png", 1, 0, 0, 0, Effect.BELOWALL, function(e, progression)
				Entity.setAngle(ship, (progression * 2 * PI) % (PI * 2) - PI / 2)
			end)
		end,
		ai          = function(m)
			local data = Entity.getExtraData(m)
			local currentTime = getTime()
			if not data.turn then
				data.popTime = currentTime
				data.turn = (math.random(0, 1) * 2 - 1) * 3
			end
			Entity.turn(m, data.turn)
			if currentTime > data.popTime + 0.01 then
				data.turn = nil
				data.popTime = currentTime
			end
		end
	}

end

do
	-- ship special 2
	
	newMissileModel{
		name        = "ShipSpecial2",
		damage      = 15,
		firePeriod  = 4.4,
		numMissiles = 30,
		angle       = PI / 3,
		speed       = 900,
		texture     = "units/ship/blue/special2.png",
		sample      = "missiles/special1.ogg"
	}
	
end

do
	-- ship special 3
	
	local numFragments = 70
	local initAngle = 0
	local radius = 50
	
	newMissileModel{
		name        = "ShipSpecial3",
		damage      = 0,
		firePeriod  = 3.8,
		numMissiles = 1,
		angle       = 0,
		speed       = 1000,
		texture     = "blank.png",
		sample      = "missiles/special1.ogg",
		pop         = function(m)
			local data = Entity.getExtraData(m)
			local currentTime = getTime()
			data.popTime = currentTime
			data.fragments = {}
			local fragments = data.fragments
			local mPos = {Entity.getPosition(m)}
			local id = Entity.getId(m)
			for i = 1, numFragments do
				local missile = popMissile{
					model    = "ShipSpecial3fragment",
					position = mPos,
					angle    = 0,
					side     = ALLY,
					params   = id
				}
				fragments[i] = Entity.getId(missile[1])
			end
		end,
		ai          = function(m)
			local data = Entity.getExtraData(m)
			local currentTime = getTime()
			local progression = (currentTime - data.popTime) * 2
			Entity.setSpeed(m, (1 - progression) * 600)
			if progression > 1 then
				local fragments = data.fragments
				for i = 1, #fragments do
					local missile = Entity.getById(fragments[i])
					if missile then
						local fragData = Entity.getExtraData(missile)
						fragData.src = nil
						fragData.splitTime = currentTime
						fragments[i] = nil
					end
				end
				Entity.destroyMissile(m)
			end
		end
	}
	
	newMissileModel{
		name        = "ShipSpecial3fragment",
		damage      = 30,
		firePeriod  = 0,
		numMissiles = 1,
		angle       = 0,
		speed       = 400,
		texture     = "units/ship/blue/special3.png",
		pop         = function(m, src)
			local data = Entity.getExtraData(m)
			data.src   = src
			initAngle  = initAngle + PI * 2 / numFragments
			data.angle = initAngle
			local srcX, srcY = Entity.getPosition(Entity.getById(src))
			Entity.setAngle(m, initAngle + PI * 1.1)
			Entity.setPosition(m, srcX + math.cos(initAngle) * radius, srcY + math.sin(initAngle) * radius)
		end,
		ai          = function(m)
			local data = Entity.getExtraData(m)
			local src = Entity.getById(data.src)
			if src then
				local srcX, srcY = Entity.getPosition(src)
				local angle = data.angle + getTime() * 5
				Entity.setAngle(m, angle + PI * 1.1)
				Entity.setPosition(m, srcX + math.cos(angle) * radius, srcY + math.sin(angle) * radius)
			else
				if not data.splitTime then
					data.splitTime = getTime()
				end
				local t = getTime() - data.splitTime + 1
				Entity.setSpeed(m, t * t * t * 600)
				Entity.turn(m, 3)
			end
		end
	}
	
end

do
	-- ship special 4
	
	local numMissiles = 36
	
	newMissileModel{
		name        = "ShipSpecial4",
		damage      = 0,
		firePeriod  = 3.2,
		numMissiles = 1,
		angle       = 0,
		speed       = 0,
		texture     = "blank.png",
		sample      = "missiles/special1.ogg",
		pop         = function(m)
			local sX = Entity.getX(getShip())
			local mY = Entity.getY(m)
			for i = 1, numMissiles do
				local angle = (i - 1) / numMissiles * 2 * PI
				popMissile{
					model    = "ShipSpecial4bis",
					position = {0, mY},
					angle    = -PI / 2,
					side     = ALLY,
					params   = {
						src = m,
						angle = angle,
						x = sX
					}
				}
			end
		end,
		ai          = function(m)
			Entity.destroyMissile(m)
		end
	}
	
	newMissileModel{
		name        = "ShipSpecial4bis",
		damage      = 30,
		firePeriod  = 0,
		numMissiles = 1,
		angle       = 0,
		speed       = 600,
		texture     = "units/ship/blue/special4.png",
		pop         = function(m, params)
			local data = Entity.getExtraData(m)
			local currentTime = getTime()
			data.popTime = currentTime
			data.src = params.src
			data.angle = params.angle
			data.x = params.x
			data.y = Entity.getY(m)
			
			Entity.setX(m, data.x)
		end,
		ai          = function(m)
			local data = Entity.getExtraData(m)
			local currentTime = getTime()
			local age = currentTime - data.popTime
			Entity.setPosition(m, data.x + math.cos(data.angle + currentTime * 10) * 120 * age, data.y - age * 600 + math.sin(data.angle + getTime() * 10) * 30 * age)
		end
	}
	
end

do
	-- ship special 5
	
	newMissileModel{
		name        = "ShipSpecial5",
		damage      = 50,
		firePeriod  = 2.6,
		numMissiles = 2,
		angle       = PI / 4,
		speed       = 800,
		texture     = "units/ship/blue/special5.png",
		sample      = "missiles/special1.ogg",
		pop         = function(m, popTime)
			local data = Entity.getExtraData(m)
			local currentTime = getTime()
			data.explodeTime = currentTime + 0.25
			data.popTime = popTime or currentTime
		end,
		ai          = function(m)
			local mX, mY = Entity.getPosition(m)
			if mY < MIN_Y or mX < MIN_X or mX > MAX_X then
				Entity.destroyMissile(m)
			else
				local angle = Entity.getAngle(m)
				local data = Entity.getExtraData(m)
				local currentTime = getTime()
				if currentTime > data.explodeTime then
					local mPos = {Entity.getPosition(m)}
					local popTime = data.popTime
					popMissile{
						model    = "ShipSpecial5",
						position = mPos,
						angle    = angle + PI / 8,
						side     = ALLY,
						params   = popTime
					}
					popMissile{
						model    = "ShipSpecial5",
						position = mPos,
						angle    = angle - PI / 8,
						side     = ALLY,
						params   = popTime
					}
					Entity.destroyMissile(m)
				else
					if angle < -PI / 2 then
						Entity.turn(m, 2)
					elseif angle > -PI / 2 then
						Entity.turn(m, -2)
					end
					local age = currentTime - data.popTime
					Entity.setSpeed(m, age * 2000)
				end
			end
		end
	}

end

do
	-- ship special 6
	
	local function special6ai(m)
		local data = Entity.getExtraData(m)
		local elapsedTime = getTime() - data.popTime
		local radius = math.exp(-elapsedTime * elapsedTime) * 400 * elapsedTime
		local angle = data.angle + elapsedTime * 14
		Entity.setAngle(m, angle)
		local mX, mY = data.x, data.y
		if elapsedTime > 0.5 then
			elapsedTime = elapsedTime - 0.5
			mY = mY - elapsedTime * (math.exp(elapsedTime) - 1) * 800
		else
			mX, mY = Entity.getPosition(getShip())
			data.x, data.y = mX, mY
		end
		Entity.setPosition(m, mX + radius * math.cos(angle), mY + radius * math.sin(angle))
	end
	
	newMissileModel{
		name        = "ShipSpecial6",
		damage      = 30,
		firePeriod  = 2,
		numMissiles = 12,
		angle       = PI / 3,
		speed       = 500,
		texture     = "units/ship/blue/special6.png",
		sample      = "missiles/special1.ogg",
		pop         = function(m)
			local mPos = {Entity.getPosition(m)}
			local angle = Entity.getAngle(m)
			local popTime = getTime()
			
			for j = 0, 0.3, 0.02 do
				for i = 0, 2 do
					popMissile{
						model    = "ShipSpecial6bis",
						position = mPos,
						angle    = angle + PI * 2 / 3 * i,
						side     = ALLY,
						params   = popTime + j
					}
				end
			end
			
			local data = Entity.getExtraData(m)
			data.x, data.y = unpack(mPos)
			data.angle = angle
			data.popTime = popTime
		end,
		ai          = function(m)
			local data = Entity.getExtraData(m)
			Entity.turn(m, math.cos((getTime() - data.popTime - 0.5) * 5) * (-PI / 2 - data.angle) * 10)
		end
	}
	
	newMissileModel{
		name        = "ShipSpecial6bis",
		damage      = 6,
		firePeriod  = 2,
		numMissiles = 1,
		angle       = PI / 3,
		speed       = 0,
		texture     = "units/ship/blue/special6bis.png",
		pop         = function(m, popTime)
			popTime = popTime or getTime()
			local data = Entity.getExtraData(m)
			data.x, data.y = Entity.getPosition(m)
			data.angle = Entity.getAngle(m)
			data.popTime = popTime
		end,
		ai          = special6ai
	}
	
end

do
	-- ship special 7
	local i = 0
	
	newMissileModel{
		name        = "ShipSpecial7",
		damage      = 15,
		firePeriod  = 1,
		numMissiles = 48,
		angle       = PI / 3,
		speed       = 2000,
		texture     = "units/ship/blue/special6.png",
		sample      = "missiles/missile1.ogg",
		pop         = function(m)
			Entity.getExtraData(m).popTime = getTime()
			i = (i + 1) % 2
			if i == 0 then
				Entity.setSpeed(m, (1 - math.cos(Entity.getAngle(m))) * 600)
			else
				Entity.setSpeed(m, (1 + math.cos(Entity.getAngle(m))) * 600)
			end
		end
	}
	
end

do
	-- Ally missiles

	newMissileModel{
		name        = "AllyMissile1",
		damage      = 3,
		firePeriod  = 0.25,
		numMissiles = 1,
		speed       = 600,
		texture     = "units/ally1/missile.png"
	}
	
end

do
	-- Missile 1

	newMissileModel{
		name        = "Missile1",
		damage      = 1,
		firePeriod  = 0.6,
		numMissiles = 1,
		speed       = 400,
		texture     = "units/enemy1/missile.png"
	}
	
end

do
	-- Missile 2

	newMissileModel{
		name        = "Missile2",
		damage      = 1,
		firePeriod  = 1,
		numMissiles = 1,
		speed       = 400,
		texture     = "units/enemy2/missile.png"
	}
	
end

do
	-- Missile 3

	newMissileModel{
		name        = "Missile3",
		damage      = 1,
		firePeriod  = 0.7,
		numMissiles = 2,
		angle       = PI / 50,
		speed       = 500,
		texture     = "units/enemy3/missile.png"
	}

	newMissileModel{
		name        = "Missile3bis",
		damage      = 1,
		firePeriod  = 0.7,
		numMissiles = 1,
		speed       = 500,
		texture     = "units/enemy3/missile.png"
	}
	
end

do
	-- Missile 4

	newMissileModel{
		name        = "Missile4",
		damage      = 1,
		firePeriod  = 0.15,
		numMissiles = 1,
		speed       = 500,
		texture     = "units/enemy4/missile.png"
	}
	
end

do
	-- Missile 5

	newMissileModel{
		name        = "Missile5",
		damage      = 1,
		firePeriod  = 0.15,
		numMissiles = 1,
		speed       = 500,
		texture     = "units/enemy5/missile.png"
	}
	
end

do
	-- Missile 6
	
	newMissileModel{
		name        = "Missile6",
		damage      = 1,
		firePeriod  = 1,
		numMissiles = 1,
		speed       = 700,
		texture     = "units/enemy6/missile.png"
	}

	newMissileModel{
		name        = "Missile6turret",
		damage      = 1,
		firePeriod  = 0.05,
		numMissiles = 1,
		speed       = 350,
		texture     = "units/enemy6/turretmissile.png"
	}
	
end

do
	-- Missile 7
	
	newMissileModel{
		name        = "Missile7",
		damage      = 1,
		firePeriod  = 0.15,
		numMissiles = 8,
		angle       = PI / 18,
		speed       = 300,
		texture     = "units/enemy7/missile.png",
		pop         = function(m)
			local mPos = { Entity.getPosition(m) }
			local mAngle = Entity.getAngle(m)
		end
	}
	
end

do
	-- Boss 1 missile

	newMissileModel{
		name        = "Boss1Missile1",
		damage      = 10,
		firePeriod  = 0.6,
		numMissiles = 2,
		angle       = PI / 36,
		speed       = 400,
		texture     = "units/boss1/missile.png"
	}

end
