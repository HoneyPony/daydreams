@type Enemy : Sprite
	vec2 velocity;

@construct
@tick

@tree
	self : Enemy
		sprite_play($, &res.enemy.enemy1_tex.loop)