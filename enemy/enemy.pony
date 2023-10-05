@type Enemy : Sprite
	vec2 velocity;
	float walk_anim_t;
	int health;

@construct
@tick

@tree
	self : Enemy
		sprite_play($, &res.enemy.enemy1_tex.loop)