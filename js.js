var xhr = new createXhrObject( ) ;
if ( !xhr) window.alert("Votre navigateur ne prend pas en charge l’objet XMLHTTPRequest.") ;

function Connexion(){
	var user = document.getElementById("user");
    var cord1 = document.getElementById("cord1");
    var cord2 = document.getElementById("cord2");
	user.innerHTML  = "Bonjour ";

	var id1 = cord1.value;
	var id2 = cord2.value;
	var params = "ident="+id1+"&pass="+id2 ;

	xhr.onreadystatechange = function() {
	    if (xhr.readyState == 4 && xhr.status == 200) {
	    	 user.innerHTML  = "Bonjour " + xhr.responseText;
	    }else
	 };

	 xhr.open("POST","http://localhost/test/test.php","true");
	xhr.send(params);
	xhr.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");