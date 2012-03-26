var screen;
var images = {};
var sounds = {};
var meters = 250;
var hours = 0;
var min = 0;
var secs = 0;
var msecs = 0;
var km_h = 0;

var key_enter = 13;

var main;
var engine;
var currentscene;

function load(){
    screen = document.getElementById("screen").getContext('2d');
    screen.save();//save initial state 1
    //load images
    var image_files = {
        "balloon": "balloon.png",
        "kitten": "pitr_Kitty_icon.png",
        "arrow": "Anonymous_Arrow_Down_Red.png"
    }
    for(var name in image_files){
        images[name] = new Image();
        images[name].src = "game/"+image_files[name];
    }
    //
    main = new Main();
    engine = new Engine();
    currentscene = main;
    setInterval(game_run, 1000/60);
}

function keydown(key){
    currentscene.keydown(key);
}

function keyup(key){
}

function draw_text(text, color, x, y){
    screen.fillStyle = color;
    screen.fillText(text, x, y);
}

//Sprite class
function Sprite(image){
    this.image = image;
    this.alpha = 1.0;
    this.x = 0;
    this.y = 0;
    this.Draw = function(){
        screen.save();
        screen.globalAlpha = this.alpha;
        screen.drawImage(this.image, this.x, this.y);
        screen.restore();
    }
    this.setAlpha = function(alpha){
        this.alpha = alpha / 255.0;}
}

//Kitten
function Kitten(){
    this.sprite = new Sprite(images["kitten"]);
    this.Update = function(){
        //Update body with sprite
    }
    this.Draw = function(){
        this.sprite.Draw();
    }
}

//Explosive
function Explosive(){
}

//Engine scene
function Engine(){
    this.kitten = new Kitten();
    this.kitten.x = 0;
    this.kitten.y = 0;
    this.kitten.sprite.setAlpha(128);
    this.explosives = new Array(7);
    for (i = 0; i < 7; i += 1){
        this.explosives[i] = new Explosive();
    }
    this.Run = function(){
        draw_text("Put some action here!", "black", 120, 120);
        this.kitten.Draw();
    }
    this.keydown = function(){
    }
}

//Main scene
function Main(){
    this.title = "Free For Fall";
    this.Run = function(){
        draw_text(this.title, "black", 64, 64);
        draw_text(meters + " meters/"+hours+":"+min+":"+secs+":"+msecs, "black", 120, 120);
        draw_text("Max km/h: "+km_h, "black", 320, 120);
        draw_text("Press enter to start", "black", 120, 240);
    }
    this.keydown = function(key){
        if (key.keyCode == key_enter){
            currentscene = engine;
        }
    }
}

document.onkeydown = keydown;
document.onkeyup = keyup;

function game_run(){
    //clear the canvas with "skyblue"
    screen.fillStyle = "skyblue";
    screen.fillRect(0, 0, 640, 480);
    //
    currentscene.Run();
}
