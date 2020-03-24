<?php

error_reporting(-1);
ini_set('display_errors', 'On');

if(isset($_POST['email']))
{
	$email_to = "erich.viebrock@gmail.com";
	$email_subject = "Message from erichviebrock.com Portfolio";
	
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

	$error_message = "";
	$string_exp = "/^[A-Za-z .'-]+$/";
	$email_exp = '/^[A-Za-z0-9._%-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,4}$/'; 
 
	if(!preg_match($string_exp,$fullName))
	{
		$error_message .= 'The name you entered does not appear to be valid.<br />';
	}
 
	if(!preg_match($email_exp,$emailFrom))
	{
		$error_message .= 'The email address you entered does not appear to be valid.<br />';
	}
 
	if(strlen($comments) < 2)
	{
		$error_message .= 'The comments you entered do not appear to be valid.<br />';
	}
 
	if(strlen($error_message) > 0)
	{
		died($error_message);
	}
 
	$email_message = "Form details below:<br/><br/>";
	
	function clean_string($string)
	{
		$bad = array("content-type","bcc:","to:","cc:","href");
		return str_replace($bad,"",$string);
	}
 
	$email_message .= "&emsp;Full Name: ".clean_string($fullName)."<br/>";
	$email_message .= "&emsp;Email: ".clean_string($emailFrom)."<br/>";
	$email_message .= "&emsp;Phone: ".clean_string($phone)."<br/>";
	$email_message .= "&emsp;Comments: ".clean_string($comments);

	$headers = array("From: ".$emailFrom,
    "Reply-To: ".$emailFrom,
    "X-Mailer: PHP/" . PHP_VERSION
	);
	$headers = implode("\r\n", $headers);

	$output = mail($email_to, $email_subject, $email_message, $headers);
	?>
	 
	Thanks for reaching out! I will get back to you very soon.

	<?php
}
?>
