
textures = {
    kitty = "pitr_Kitty_icon.png",
    floor = "floor.png",
    arrow = "Anonymous_Arrow_Down_Red.png",
    cross = "raemi_Cross_Out.png",
    balloon = "balloon.png",
    bomb = "Bomb.png",
    explosion = "1270762888.png",
    flames = "Anonymous_Fireball.png",
    bg = "bg.png",
    smoke = "smoke.png"
}

fonts = {
    baroque = "BaroqueScript.ttf"
}

--In code, sounds are soundbuffers and sounds are channels for play the soundbuffers
sounds = {
    pop = "Balloon Pop_Sound-14025-Free-Loops.com.wav",
    explosion = "Explosion Sounds.wav-21336-Free-Loops.com.wav",
    crash = "BRG-Louis_Le-24.wav",
    burstinflames = "Woff-Raphael-2141.wav",
    bounce = "Bouncing-Michael_-100.wav",
}

musics = {
    theme = "03_fall_down_to_the_scream.flac",
}

engine = {
    startpos = -250;--meters
    startvel = 80;--km/h
    explosiveeach = 200,--ms
    explosivefalling = 75,--%
    explosiveascending = 50,--%
}

arrow = {
    texture = "arrow",
    originx = 15.5,
    originy = 32,
}

cross = {
    texture = "cross",
    originx = 16,
    originy = 16,
}

bomb = {
    texture = "bomb",
    originx = 20,
    originy = 40,
}

kitty = {
    originx = 32,
    originy = 32,
    radius = 24,
}

flames = {
    originx = 113/2,
    originy = 222,
}

smoke = {
    originx = 16,
    originy = 16,
}

balloon = {
    signal = arrow,
    texture = "balloon",
    originx = 24,
    originy = 32,
    radius = 24,
    impulse = -80,--km/h
    appareance = 50,--%
    sound = "pop"
}

bomb_explosive = {
    signal = bomb,
    texture = "bomb",
    originx = bomb.originx,
    originy = bomb.originy,
    radius = 20,
    impulse = -250,--km/h
    appareance = 5,--%
    sound = "explosion"
}

cross_explosive = {
    signal = cross,
    texture = "cross",
    originx = cross.originx,
    originy = cross.originy,
    radius = 16,
    impulse = 500,--down
    appareance = 100,
    sound = "bounce",
}

explosives = {
    ["balloon"] = balloon,
    ["bomb_explosive"] = bomb_explosive,
    ["cross_explosive"] = cross_explosive,
}
