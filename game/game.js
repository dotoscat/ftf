var screen;
var images;
var sounds;
var meters = 250;
var hours = 0;
var min = 0;
var secs = 0;
var msecs = 0;
var km_h = 0;

var currentscene;

var key_enter = 13;

function load(){
    screen = document.getElementById("screen").getContext('2d');
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
            this.title = "Game started!";
        }
    }
}

//Engine scene
function Engine(){
}

currentscene = new Main();
var main = currentscene;
document.onkeydown = keydown;

function game_run(){
    //clear the canvas with "skyblue"
    screen.fillStyle = "skyblue";
    screen.fillRect(0, 0, 640, 480);
    //
    currentscene.Run();
}
