@type Player : Node
	vec2 velocity;

@construct
@tick

@tree
	self : Player

	sprite : Sprite
		parent = self
		sprite_play($, &res.player.player_tex.loop)