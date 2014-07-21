local function registerEffect(params)
	local texture = params.texture
	local duration = params.duration
	local layer = params.layer
	local animation = params.animation
	return function(x, y, z)
		Effect.add(texture, duration, x, y, z, layer, animation)
	end
end

local effectsData = {}

Effect.models = {

	blueFire = registerEffect{
		texture   = "units/ship/blue/fire.png",
		duration  = 0.05,
		layer     = Effect.ABOVE,
		animation = function(e, progression, step, stepProgression)
			Effect.setAlpha(e, 1 - progression)
			Effect.setZ(e, 40)
		end
	},

	explosion = registerEffect{
		texture   = "effects/explosion",
		duration  = 1,
		layer     = Effect.BELOWALL,
		animation = function(e, progression, step, stepProgression)
			if not effectsData[e] then
				local v = (math.random() + 1) * 50
				local d = math.random() * math.pi * 2
				local x, y = Effect.getPosition(e)
				effectsData[e] = {
					a = math.random() * math.pi * 2,
					vx = math.cos(d) * v,
					vy = math.sin(d) * v,
					x = x,
					y = y
				}
			end
			local data = effectsData[e]
			Effect.setAlpha(e, 1 - progression)
			Effect.setScale(e, 1 - progression / 2)
			Effect.setRotationZ(e, progression * 10 + data.a)
			Effect.setPosition(e, data.x + data.vx * progression, data.y + data.vy * progression, 0)
			if progression == 1 then
				effectsData[e] = nil
			end
		end
	}

}

