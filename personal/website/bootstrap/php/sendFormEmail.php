<?php

error_reporting(-1);
ini_set('display_errors', 'On');

if(isset($_POST['email']))
{
	$emailTo = "erich.viebrock@gmail.com";
	$emailsubject = "Message from erichviebrock.com Portfolio";
	
	function died($error)
	{
		echo "Sorry to say, but there were error(s) found with the form you submitted. ";
		echo "These error(s) appear below:<br /><br />";
		echo $error."<br /><br />";
		echo "Please go back and fix these error(s).<br /><br />";
		die();
	}
 
	if(!isset($_POST['fullName']) ||
		!isset($_POST['email']) ||
		!isset($_POST['phone']) ||
		!isset($_POST['comments']))
	{
		died('We are sorry, but there appears to be a problem with the form you submitted.');
	}
 
	$fullName = $_POST['fullName'];
	$emailFrom = $_POST['email'];
	$phone = $_POST['phone'];
	$comments = $_POST['comments'];

	$errorMessage = "";
	$stringExp = "/^[A-Za-z .'-]+$/";
	$emailExp = '/^[A-Za-z0-9._%-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,4}$/'; 
 
	if(!preg_match($stringExp,$fullName))
	{
		$errorMessage .= 'The name you entered does not appear to be valid.<br />';
	}
 
	if(!preg_match($emailExp,$emailFrom))
	{
		$errorMessage .= 'The email address you entered does not appear to be valid.<br />';
	}
 
	if(strlen($comments) < 2)
	{
		$errorMessage .= 'The comments you entered do not appear to be valid.<br />';
	}
 
	if(strlen($errorMessage) > 0)
	{
		died($errorMessage);
	}
 
	$emailMessage = "Form details below:<br/><br/>";
	
	function clean_string($string)
	{
		$bad = array("content-type","bcc:","to:","cc:","href");
		return str_replace($bad,"",$string);
	}
 
	$emailMessage .= "&emsp;Full Name: ".clean_string($fullName)."<br/>";
	$emailMessage .= "&emsp;Email: ".clean_string($emailFrom)."<br/>";
	$emailMessage .= "&emsp;Phone: ".clean_string($phone)."<br/>";
	$emailMessage .= "&emsp;Comments: ".clean_string($comments);

	$headers = array("From: ".$emailFrom,
    "Reply-To: ".$emailFrom,
    "X-Mailer: PHP/" . PHP_VERSION
	);
	$headers = implode("\r\n", $headers);

	$output = mail($emailTo, $emailSubject, $emailMessage, $headers);
	
	if (!$output) {
   	print_r(error_get_last()['message']);
	}
	
	?>
	 
	Thanks for reaching out! I will get back to you very soon.

	<?php
}
?>
