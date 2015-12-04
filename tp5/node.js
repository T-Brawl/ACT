var fs = require('fs');

console.log(process.argv);

function shuffle(a){
    var j = 0;
    var valI = '';
    var valJ = valI;
    var l = a.length - 1;
    while(l > -1){
	j = Math.floor(Math.random() * l);
	valI = a[l];
	valJ = a[j];
	a[l] = valJ;
	a[j] = valI;
	l = l - 1;
    }
    return a;
}


function init(filename){
    var data=fs.readFileSync(filename,'utf8');
    data =data.split('\n');
    var entry= data[0].split(' ');
    //reindex to avoid many -1
    for(var i = 0; i<entry[0];i++){
	data[i]=data[i+1];
    }
    data.splice(-1,1);
    return {arr:data,entry:entry};
}

function create_parts_since(data,i,j,parts){
    var mmax=i+data.entry[3];
    for(var m=i;m<mmax && m<data.entry[0];m++){
	var ham=0;
	var cases=0;
	for(var n=j;cases< data.entry[3] && n<data.entry[1];n++){
	    for(var o=i; o<=m;o++){
		cases++;
		if(data.arr[o][n]=='H') ham++;
	    }
	    if((cases<=data.entry[3])&&(ham>= data.entry[2])){
		parts.push({x1:i,y1:j,x2:m,y2:n});
	    }
	}
    }
    //console.log('parts ', parts);
}

function create_parts(data){
    var parts=[];
    for(var i=0;i<data.entry[0];i++){
	for(var j=0;j<data.entry[1];j++){
	    console.log('i',i,'j',j);
	    create_parts_since(data,i,j,parts);
	};
    };
    console.log(parts);
    return parts;
}

function select_one(tmp, select,part){
    function aux(x,y){
	
	if(y>ymax){
	    if(x>=xmax){
		return true;
	    }else{
		return aux(x+1, ymin);
	    }
	}else if(tmp[x][y]){
	    return false;
	}else {
	    if(aux(x,y+1)){
		tmp[x][y]=select.length+1;
		return true
	    }else{
		return false;
	    }
	}
    }

    var xmax= part.x2;
    var ymax= part.y2;
    var ymin= part.y1;
    if(aux(part.x1,part.y1)){
	select.push(part);
    }
	
}

function select_random_parts(data,parts){
    shuffle(parts);
    var tmp=[];
    var select=[];
    for(var i=0;i<data.entry[0];i++){
	tmp.push([]);
    }
    for(var ind in parts){
	select_one(tmp, select,parts[ind]);
    }
    console.log('----------------------------');
    for(i=0;i<tmp.length;i++){
	console.log(tmp[i]);
    }
    console.log('----------------------------');
    return select;
}

function search(filename){
    var data = init(filename);
    var parts=create_parts(data);
    console.log(parts);
    var selected_parts= select_random_parts(data,parts);
    console.log(selected_parts);
}

search(process.argv[2]);
console.log('end prog');
