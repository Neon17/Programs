window.onload = function () {
    var node = document.getElementsByClassName("boxitem");
    for (var i = 0; i < 8; i++) {
        console.log(node[i]);
    }
    var boxes = document.getElementById("boxes");
    setBigBoxValue(boxes);

}
function setBigBoxValue(boxes){
    var boxesHeight = 500;
    var boxesWidth = 500;
    boxes.style.width = boxesWidth.toString()+"px";
    boxes.style.height = boxesHeight.toString()+"px";
    var box = document.getElementsByClassName("boxitem");
    console.log(box);
    //setBigBoxValue(box);
}
/*function setBoxValue(box){
    for (var i=0; i<8; i++){
        box[i].style.width = "100px";
        box[i].style.height = "12px";
        box[i].style.backgroundColor = "aliceblue";
    }
}*/