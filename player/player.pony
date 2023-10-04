@type Player : Node
	vec2 velocity;

	float walk_anim_t;
	float walk_vel_rot_smoothed;

@construct
@tick

@tree
	self : Player

	sprite : Sprite
		parent = self
		sprite_play($, &res.player.player_tex.loop)