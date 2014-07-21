local math = math
local PI = math.pi
local yield = coroutine.yield

-- wait functions
local function waitUntilNoEnemy()
	repeat
		yield()
	until getNumEnemies() == 0
end

local function wait(duration)
	local waitTime = getTime() + duration
	repeat
		yield()
	until getTime() >= waitTime
end

-- music manager
local MusicManager = {}

function MusicManager:new()
	return setmetatable({}, { __index = self })
end

function MusicManager:setMusic(musicName, duration)
	duration = duration or 1
	local music = self.musics[musicName]
	local currentMusic = self.currentMusic
	if music == currentMusic then
		return
	end
	Music.play(music)
	local t = getTime()
	repeat
		local t2 = getTime()
		local transition = (t2 - t) / duration
		if currentMusic then
			Music.setVolume(currentMusic, 100 * (1 - transition))
		end
		Music.setVolume(music, 100 * transition)
		yield()
	until t2 >= t + duration
	if currentMusic then
		Music.stop(currentMusic)
	end
	self.currentMusic = music
end

function MusicManager:load(files)
	local musics = self.musics or {}
	for name, file in pairs(files) do
		musics[name] = Music.get("music/"..file)
	end
	self.musics = musics
end

-- lvl up scores
addLevelUpScore(2000)
addLevelUpScore(4500)
addLevelUpScore(11000)
addLevelUpScore(15500)
addLevelUpScore(20000)

-- musics
local mm = MusicManager:new()

mm:load{
	enemy1 = "a_war_without_weapons.ogg",
	enemy4 = "musique_d_ailleurs.ogg",
	boss   = "a_journey_in_my_mind.ogg"
}


return coroutine.create(function()

	local CENTER_X, CENTER_Y, MIN_X, MIN_Y, MAX_X, MAX_Y = CENTER_X, CENTER_Y, MIN_X, MIN_Y, MAX_X, MAX_Y
	
	Entity.newShield(getShip(), 10000)
	
	mm:setMusic("enemy1")
	--[[
	popUnit{
		model      = "Enemy8",
		position   = { CENTER_X, -100 },
		angle      = PI / 2,
		invincible = true,
		side       = ENEMY
	}
	
	waitUntilNoEnemy()
	]]
	------------------------------------
	-- Enemy 1
	------------------------------------
	
	do
		local waitTime = 2.1
		
		while waitTime >= 0.6 do
			local numUnits = 6
			local i = 0
			while i < numUnits do
				popUnit{
					model    = "Enemy1l",
					position = { CENTER_X - 30 + i * 30, -100 },
					angle    = PI / 2 + PI / 12,
					side     = ENEMY
				}
				i = i + 1
			end
			
			wait(waitTime)
			
			local numUnits = 6
			local i = 0
			while i < numUnits do
				popUnit{
					model    = "Enemy1r",
					position = { CENTER_X + 30 - i * 30, -100 },
					angle    = PI / 2 - PI / 12,
					side     = ENEMY
				}
				i = i + 1
			end
			
			wait(waitTime)
			
			waitTime = waitTime - 0.15
		end
	end
	
	------------------------------------
	
	wait(2)
	
	------------------------------------
	-- Enemy 2 & 3
	------------------------------------
	
	do
		local x = 300
		local waitTime = 4
		local abs = math.abs
		while abs(x) > 50 do
			popUnit{
				model    = "Enemy2",
				position = { CENTER_X - x, -100 },
				angle    = PI / 2,
				side     = ENEMY
			}
			popUnit{
				model    = "Enemy3",
				position = { CENTER_X + x, -100 },
				angle    = PI / 2,
				side     = ENEMY
			}
			wait(waitTime)
			x = x / -1.2
			waitTime = waitTime * 0.9
		end
	end
	
	------------------------------------
	
	mm:setMusic("enemy4", 2)
	
	------------------------------------
	-- Enemy 4
	------------------------------------
	
	do
		local waitTime = 5
		while waitTime > 0 do
			popUnit{
				model    = "Enemy4",
				position = { CENTER_X + 100, -100 },
				angle    = PI / 2,
				side     = ENEMY,
				params   = 1
			}
			wait(waitTime)
			popUnit{
				model    = "Enemy4",
				position = { CENTER_X - 100, -100 },
				angle    = PI / 2,
				side     = ENEMY,
				params   = -1
			}
			wait(waitTime)
			waitTime = waitTime - 0.5
		end
	end
	
	------------------------------------
	
	wait(2)
	waitUntilNoEnemy()
	
	------------------------------------
	-- Enemy 5
	------------------------------------
	
	do
		local rowWidth = 50
		
		for numRows = 1, 3 do
			for i = 0, numRows - 1 do
				for j = 0, numRows - 1 do
					popUnit{
						model    = "Enemy5",
						position = { CENTER_X - (numRows - 1) / 2 * rowWidth + i * rowWidth, -200 + (numRows - j) * rowWidth },
						angle    = PI / 2,
						side     = ENEMY,
						params   = -1
					}
					popUnit{
						model    = "Enemy5",
						position = { CENTER_X - (numRows - 1) / 2 * rowWidth + i * rowWidth, -200 + (numRows - j) * rowWidth },
						angle    = PI / 2,
						side     = ENEMY,
						params   = 1
					}
				end
			end
			waitUntilNoEnemy()
		end
		
		local numRows = 4
		
		for i = 0, numRows - 1 do
			for j = 0, numRows - 1 do
				popUnit{
					model    = "Enemy5",
					position = { CENTER_X - (numRows - 1) / 2 * rowWidth + i * rowWidth, -200 + (numRows - j) * rowWidth },
					angle    = PI / 2,
					side     = ENEMY,
					params   = -1
				}
			end
		end
		waitUntilNoEnemy()
		
		for i = 0, numRows - 1 do
			for j = 0, numRows - 1 do
				popUnit{
					model    = "Enemy5",
					position = { CENTER_X - (numRows - 1) / 2 * rowWidth + i * rowWidth, -200 + (numRows - j) * rowWidth },
					angle    = PI / 2,
					side     = ENEMY,
					params   = 1
				}
			end
		end
		waitUntilNoEnemy()
		
	end
	
	------------------------------------
	
	wait(2)
	
	------------------------------------
	-- Enemy 6
	------------------------------------
	
	do
		for numTurrets = 1, 3 do
			popUnit{
				model    = "Enemy6",
				position = { CENTER_X - 70, MIN_Y },
				angle    = PI / 2,
				side     = ENEMY,
				params   = { num = numTurrets, direction = PI / 2 }
			}
			popUnit{
				model    = "Enemy6",
				position = { CENTER_X + 70, MIN_Y },
				angle    = PI / 2,
				side     = ENEMY,
				params   = { num = numTurrets, direction = PI / 2 }
			}
			waitUntilNoEnemy()
		end
	end
	
	------------------------------------
	-- Enemy 7
	------------------------------------
	
	do
		for numEnemies = 3, 6 do
			for i = 1, numEnemies do
				popUnit{
					model    = "Enemy7",
					position = { CENTER_X + (i - numEnemies / 2) * 100, MIN_Y },
					angle    = PI / 2,
					side     = ENEMY
				}
			end
			waitUntilNoEnemy()
		end
	end
	
	------------------------------------
	
	-- wait(2)
	mm:setMusic("boss", 2)
	
	------------------------------------
	-- Boss
	------------------------------------
	
	do
		popUnit{
			model      = "Boss1",
			position   = { CENTER_X, CENTER_Y },
			angle      = PI / 2,
			invincible = true,
			side       = ENEMY
		}
	end
	
	------------------------------------
	
	do
		popUnit{
			model    = "Ally1l",
			position = { CENTER_X, MAX_Y },
			angle    = 0,
			side     = ALLY
		}
		popUnit{
			model    = "Ally1r",
			position = { CENTER_X, MAX_Y },
			angle    = 0,
			side     = ALLY
		}
	end
	
end)
