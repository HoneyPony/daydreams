@type Arrow : Sprite
	vec2 velocity;
	float lifetime;

	SpatialHashRef ref;

@construct
@tick
@destruct

@header
	void arrow_spawn(Player *parent);
	extern SpatialHash arrow_hash;

@tree
	self : Arrow
		sprite_play($, &res.player.arrow_spawn_tex.loop)