var screen;
var images;
var sounds;
var meters = 250;
var hours = 0;
var min = 0;
var secs = 0;
var msecs = 0;
var km_h = 0;

var key_enter = 13;

function load(){
    screen = document.getElementById("screen").getContext('2d');
    screen.save();//save initial state 1
    images = new Array();
    sounds = new Array();
    setInterval(game_run, 1000/60);
}

function keydown(key){
    currentscene.keydown(key);
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
        screen.globalAlpha = this.alpha;
        screen.drawImage(this.image, x, y);
        screen.globalAlpha = 1.0;
    }
    this.setAlpha = function(alpha){
        this.alpha = this.alpha / 255.0;}
}

//Engine scene
function Engine(){
    this.something = 12;
    this.Run = function(){
        draw_text("Put some action here!", "black", 120, 120);
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

var main = new Main();
var engine = new Engine();
var currentscene = main;
document.onkeydown = keydown;

function game_run(){
    //clear the canvas with "skyblue"
    screen.fillStyle = "skyblue";
    screen.fillRect(0, 0, 640, 480);
    //
    currentscene.Run();
}
