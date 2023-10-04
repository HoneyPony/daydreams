@type Arrow : Sprite
	vec2 velocity;
	float lifetime;

@construct
@tick

@header
	void arrow_spawn(Player *parent);

@tree
	self : Arrow
		sprite_play($, &res.player.arrow_spawn_tex.loop)