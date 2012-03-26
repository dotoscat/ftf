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
    screen.globalAlpha = 1.0;
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
        screen.globalAlpha = this.alpha;
        screen.drawImage(this.image, this.x, this.y);
    }
    this.setAlpha = function(alpha){
        this.alpha = alpha / 255.0;}
}

function Text(str){
    this.str = str;
    this.alpha = 1.0;
    this.x = 0;
    this.y = 0;
    
    this.Draw = function(){
        screen.globalAlpha = this.alpha;
        screen.fillStyle = color;
        screen.fillText(text, x, y);
    }
    
    this.setAlpha = function(alpha){
        this.alpha = alpha / 255.0;}
        
}

//Kitten
function Kitten(body){
    this.sprite = new Sprite(images["kitten"]);
    this.body = body;
    
    this.Update = function(){
        var pos = this.body.GetPosition();
        meters = pos.y;
        this.sprite.x = pos.x;
        this.sprite.y = pos.y;
    }
    
    this.Draw = function(){
        this.sprite.Draw();
    }
    
}

//Explosive
function Explosive(){
    this.Draw = function(){
    }
}

//Engine scene
function Engine(){
    this.explosives = new Array(7);
    this.world = new Box2D.Dynamics.b2World(new Box2D.Common.Math.b2Vec2(0.0, 9.8), true);
    
    var basicbodydef = new Box2D.Dynamics.b2BodyDef();
    basicbodydef.type = 2;//dynamic
    
    this.kitten = new Kitten(this.world.CreateBody(basicbodydef));
    this.kitten.sprite.x = 320;
    this.kitten.sprite.y = 320;
    this.kitten.sprite.setAlpha(50);
    
    for (i = 0; i < 7; i += 1){
        this.explosives[i] = new Explosive();
    }
    
    this.Run = function(){
        this.world.Step(1000/60);
        draw_text("Put some action here!", "black", 120, 120);
        for (i = 0; i < 7; i += 1){
            this.explosives[i].Draw();
        }
        this.kitten.Update();
        this.kitten.Draw();
        draw_text(meters+" meters", "black", 16, 6);
        draw_text(hours+":"+min+":"+secs+":"+msecs, "black", 320, 32);
        draw_text(km_h+" km/h", "black", 0, 32);
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
