local math = math
local PI = math.pi

do
	-- Ally 1
	
	local function ally1pop(u)
		Entity.newShield(u, 200)
	end
	
	local function ally1ai(sign)
		return function(u)
			local ship = getShip()
			local shipX, shipY = Entity.getPosition(ship)
			local uX, uY = Entity.getPosition(u)
			local dstX, dstY = shipX - 50 * sign, math.max(shipY - 40, MIN_Y)
			dstX = math.min(math.max(dstX, MIN_X), MAX_X)
			local distSq = (uX - dstX) * (uX - dstX) + (uY - dstY) * (uY - dstY)
			if distSq > 50 then
				Entity.setDirection(u, dstX, dstY)
				Entity.setSpeed(u, math.min((distSq + 600) / 5, 600))
			else
				Entity.setSpeed(u, 0)
				local angle = (Entity.getAngle(u) - PI / 2) % (PI * 2) - PI
				if angle < -0.04 then
					Entity.turn(u, 20)
					local angle = (Entity.getAngle(u) - PI / 2) % (PI * 2) - PI
					if angle > 0.04 then
						Entity.setAngle(u, -PI / 2)
					end
				elseif angle > 0.04 then
					Entity.turn(u, -20)
					local angle = (Entity.getAngle(u) - PI / 2) % (PI * 2) - PI
					if angle < -0.04 then
						Entity.setAngle(u, -PI / 2)
					end
				else
					Entity.setAngle(u, -PI / 2)
				end
			end
		end
	end

	newUnitModel{
		name    = "Ally1l",
		missile = "AllyMissile1",
		health  = 1,
		speed   = 300,
		texture = "units/ally1",
		pop     = ally1pop,
		ai      = ally1ai(-1)
	}

	newUnitModel{
		name    = "Ally1r",
		missile = "AllyMissile1",
		health  = 1,
		speed   = 300,
		texture = "units/ally1",
		pop     = ally1pop,
		ai      = ally1ai(1)
	}

end

do
	-- Enemy 1
	
	local function enemy1ai(sign)
		return function(u)
			Entity.turn(u, 0.04 * sign)
		end
	end

	newUnitModel{
		name    = "Enemy1l",
		missile = "Missile1",
		health  = 15,
		speed   = 200,
		texture = "units/enemy1",
		ai      = enemy1ai(-1)
	}

	newUnitModel{
		name    = "Enemy1r",
		missile = "Missile1",
		health  = 15,
		speed   = 200,
		texture = "units/enemy1",
		ai      = enemy1ai(1)
	}

end

do
	-- Enemy 2

	newUnitModel{
		name    = "Enemy2",
		missile = "Missile2",
		health  = 30,
		speed   = 150,
		texture = "units/enemy2"
	}

end

do
	-- Enemy 3

	newUnitModel{
		name    = "Enemy3",
		missile = "Missile3",
		health  = 120,
		speed   = 100,
		texture = "units/enemy9",
		ai      = function(u)
			local uPos = { Entity.getPosition(u) }
			if uPos[2] > 180 then
				local health = Entity.getHealth(u) / 2
				do
					local u = popUnit{
						model    = "Enemy3r",
						position = uPos,
						angle    = PI / 2,
						side     = ENEMY
					}
					Entity.setHealth(u, health)
				end
				do
					local u = popUnit{
						model    = "Enemy3l",
						position = uPos,
						angle    = PI / 2,
						side     = ENEMY
					}
					Entity.setHealth(u, health)
				end
				Entity.destroyUnit(u)
			end
		end
	}

	newUnitModel{
		name    = "Enemy3l",
		missile = "Missile3bis",
		health  = 60,
		speed   = 100,
		texture = "units/enemy9",
		ai      = function(u)
			Entity.turn(u, -0.07)
		end
	}

	newUnitModel{
		name    = "Enemy3r",
		missile = "Missile3bis",
		health  = 60,
		speed   = 100,
		texture = "units/enemy9",
		ai      = function(u)
			Entity.turn(u, 0.07)
		end
	}

end

do
	-- Enemy 4

	newUnitModel{
		name    = "Enemy4",
		missile = "ShipMissile1",
		health  = 200,
		speed   = 150,
		texture = "units/enemy4",
		pop     = function(u, sign)
			local data = Entity.getExtraData(u)
			data.nextExplosion = getTime() + 0.15
			data.sign = sign
		end,
		ai      = function(u)
			local currentTime = getTime()
			local data = Entity.getExtraData(u)
			if currentTime > data.nextExplosion then
				data.nextExplosion = currentTime + 0.15
			end
			if not data.beginSlalom then
				if Entity.getY(u) > 100 then
					data.beginSlalom = currentTime
				end
			else
				Entity.turn(u, data.sign * math.cos((data.beginSlalom - currentTime) * 5) * 5)
			end
		end
	}

end

do
	-- Enemy 5
	
	newUnitModel{
		name    = "Enemy5",
		missile = "Missile5",
		health  = 200,
		speed   = 200,
		texture = "units/enemy5",
		pop     = function(u, sign)
			local data = Entity.getExtraData(u)
			data.popTime = getTime()
			data.turn = sign * 2
		end,
		ai      = function(u)
			local data = Entity.getExtraData(u)
			if data.popTime + 2 < getTime() then
				Entity.turn(u, data.turn)
			end
		end
	}
end

do
	-- Enemy 6
	
	newUnitModel{
		name    = "Enemy6",
		missile = "Missile6",
		health  = 10000,
		speed   = 0,
		texture = "units/enemy6",
		pop     = function(u, params)
			local data = Entity.getExtraData(u)
			params = params or {}
			data.num = params.num or 1
			data.behavior = params.behavior or function() return 1 end
			data.direction = params.direction or PI / 2
			data.turretsSpawnTime = getTime() + 1.7
		end,
		ai      = function(u)
			local data = Entity.getExtraData(u)
			local minSpeed = 25
			local speed = math.max((data.turretsSpawnTime - getTime()) * 300, minSpeed)
			if speed == minSpeed then
				if not data.turretsSpawned then
					Entity.setSpeed(u, minSpeed)
					local numTurrets = data.num
					for i = 0, numTurrets - 1 do
						popUnit{
							model    = "Enemy6turret",
							position = {0, 0},
							angle    = i / numTurrets * 2 * PI + data.direction,
							side     = ENEMY,
							params   = { controller = u, behavior = data.behavior }
						}
					end
					data.turretsSpawned = true
				end
			else
				Entity.setSpeed(u, speed)
			end
		end
	}
	
	newUnitModel{
		name    = "Enemy6turret",
		missile = "Missile6turret",
		health  = 15000,
		speed   = 0,
		texture = "units/enemy6/turret",
		pop     = function(u, params)
			local data = Entity.getExtraData(u)
			data.controllerId = Entity.getId(params.controller)
			data.behavior = params.behavior
			Entity.setPosition(u, Entity.getPosition(params.controller))
		end,
		ai      = function(u)
			local data = Entity.getExtraData(u)
			local controller = Entity.getById(data.controllerId)
			if controller then
				Entity.setPosition(u, Entity.getPosition(controller))
				Entity.turn(u, data.behavior())
			else
				Entity.destroyUnit(u)
			end
		end
	}
	
end

do
	-- Enemy 7
	
	newUnitModel{
		name    = "Enemy7",
		missile = "Missile7",
		health  = 10000,
		speed   = 100,
		texture = "units/enemy7",
		ai      = function(u)
			Entity.lookAt(u, getShip())
		end
	}
	
end

do
	-- Enemy 9
	newUnitModel{
		name    = "Enemy8",
		missile = "NoMissile",
		health  = 10000,
		speed   = 100,
		texture = "units/enemy8/body",
		pop     = function(u, params)
			local data = Entity.getExtraData(u)
			data.leftWing = popUnit{
				model    = "Enemy8l",
				position = { 0, 0 },
				angle    = PI / 2,
				side     = ENEMY,
				params   = u
			}
			data.rightWing = popUnit{
				model    = "Enemy8r",
				position = { 0, 0 },
				angle    = PI / 2,
				side     = ENEMY,
				params   = u
			}
		end,
		ai      = function(u)
			Entity.lookAt(u, getShip())
		end
	}
	
	newUnitModel{
		name    = "Enemy8l",
		missile = "NoMissile",
		health  = 10000,
		speed   = 0,
		texture = "units/enemy8/leftwing",
		pop     = function(u, body)
			Entity.getExtraData(u).body = body
		end,
		ai      = function(u)
			local body = Entity.getExtraData(u).body
			local bX, bY = Entity.getPosition(body)

			local angle = Entity.getAngle(body)
			local x = -24
			local y = -24
			
			local time = getTime()
			
			x = x + 5 * math.cos(time * 4)
			y = y + 5 * math.cos(time * 4)
			
			local a = angle + PI / 2
			local lX = math.cos(a) * x - math.sin(a) * y
			local lY = math.sin(a) * x + math.cos(a) * y
			
			Entity.setPosition(u, bX + lX, bY + lY)
			Entity.setAngle(u, angle)
		end
	}
	
	newUnitModel{
		name    = "Enemy8r",
		missile = "NoMissile",
		health  = 10000,
		speed   = 0,
		texture = "units/enemy8/rightwing",
		pop     = function(u, body)
			Entity.getExtraData(u).body = body
		end,
		ai      = function(u)
			local body = Entity.getExtraData(u).body
			local bX, bY = Entity.getPosition(body)

			local angle = Entity.getAngle(body)
			local x = 24
			local y = -24
			
			local time = getTime()
			
			x = x - 5 * math.cos(time * 4)
			y = y + 5 * math.cos(time * 4)
			
			local a = angle + PI / 2
			local lX = math.cos(a) * x - math.sin(a) * y
			local lY = math.sin(a) * x + math.cos(a) * y
			
			Entity.setPosition(u, bX + lX, bY + lY)
			Entity.setAngle(u, angle)
		end
	}
	
end

do
	-- Boss 1

	newUnitModel{
		name    = "Boss1",
		missile = "NoMissile",
		health  = 2000,
		speed   = 0,
		texture = "units/boss1/head.png",
		pop     = function(u)
			local data = Entity.getExtraData(u)
			data.popTime = getTime()
			
			Entity.setPosition(u, CENTER_X, -200)
			
			local leftArm = popUnit{
				model    = "Boss1LeftArm",
				position = {0, 0},
				angle    = PI / 2,
				side     = ENEMY,
				params   = u
			}
			
			local rightArm = popUnit{
				model    = "Boss1RightArm",
				position = {0, 0},
				angle    = PI / 2,
				side     = ENEMY,
				params   = u
			}
			
			data.leftArm  = Entity.getId(leftArm)
			data.rightArm = Entity.getId(rightArm)
			
		end,
		ai      = function(u)
			local data = Entity.getExtraData(u)
			local currentTime = getTime()
			if not data.killTime then
				local leftArm  = Entity.getById(data.leftArm)
				local rightArm = Entity.getById(data.rightArm)
				local progression = (getTime() - data.popTime) / 5
				if progression <= 1 then
					Entity.setSpeed(u, (1 - progression) * 150)
				else
					Entity.setSpeed(u, 0)
				end
				if leftArm or rightArm then
					Entity.setX(u, CENTER_X + math.cos(currentTime - Entity.getExtraData(u).popTime) * 200)
				else
					data.killTime = currentTime
				end
			else
				local progression = (currentTime - data.killTime) / 5
				if progression < 1 then
					Entity.setAngle(u, PI / 2 + progression * progression * progression * progression * 50)
				else
					Entity.killUnit(u)
				end
			end
		end
	}

	newUnitModel{
		name    = "Boss1LeftArm",
		missile = "Boss1Missile1",
		health  = 4000,
		speed   = 0,
		texture = "units/boss1/leftarm.png",
		pop     = function(u, boss)
			local data = Entity.getExtraData(u)
			data.boss = boss
			
			local bX, bY = Entity.getPosition(boss)
			local currentTime = getTime()
			local angle = (currentTime - Entity.getExtraData(boss).popTime) * 5
			local radius = 30
			local uAngle = PI / 2 + math.cos(angle / 3) / 3
			
			Entity.setPosition(u, bX - 128 - math.cos(angle) * radius, bY + math.sin(angle) * radius)
			Entity.setAngle(u, uAngle)
			
			Entity.setHealth(u, 40000)
		end,
		ai      = function(u)
			local data = Entity.getExtraData(u)
			local boss = data.boss
			
			local bX, bY = Entity.getPosition(boss)
			local currentTime = getTime()
			local angle = (currentTime - Entity.getExtraData(boss).popTime) * 5
			local radius = 30
			local uAngle = PI / 2 + math.cos(angle / 3) / 3
			
			Entity.setPosition(u, bX - 128 - math.cos(angle) * radius, bY + math.sin(angle) * radius)
			Entity.setAngle(u, uAngle)
		end
	}

	newUnitModel{
		name    = "Boss1RightArm",
		missile = "Boss1Missile1",
		health  = 4000,
		speed   = 0,
		texture = "units/boss1/rightarm.png",
		pop     = function(u, boss)
			local data = Entity.getExtraData(u)
			data.boss = boss
			
			local bX, bY = Entity.getPosition(boss)
			local currentTime = getTime()
			local angle = (currentTime - Entity.getExtraData(boss).popTime) * 5
			local radius = 30
			local uAngle = PI / 2 + math.cos(angle / 3) / 3
			
			Entity.setPosition(u, bX + 128 + math.cos(angle) * radius, bY + math.sin(angle) * radius)
			Entity.setAngle(u, uAngle)
			
			Entity.setHealth(u, 40000)
		end,
		ai      = function(u)
			local data = Entity.getExtraData(u)
			local boss = data.boss
			
			local bX, bY = Entity.getPosition(boss)
			local currentTime = getTime()
			local angle = (currentTime - Entity.getExtraData(boss).popTime) * 5
			local radius = 30
			local uAngle = PI / 2 - math.cos(angle / 3) / 3
			
			Entity.setPosition(u, bX + 128 + math.cos(angle) * radius, bY + math.sin(angle) * radius)
			Entity.setAngle(u, uAngle)
		end
	}

end
