<%@ LANGUAGE=JScript %>

<html>

<head>

<title>Create Mail</title>

<script for=send event="onclick()" language=jscript>  
  if (from.value == "")
  {
    alert("You must fill in the From field");
    return;
  }

  if (to.value == "")
  {
    alert("You must fill in the To field");
    return;
  }

  if (subject.value == "")
  {
    if (!confirm("You have a blank subject field. Is that okay?"))
      return;
  }

  if (msg.value == "")
  {
    if (!confirm("You have a blank message. Is that okay?"))
      return;
  }

   submit();
</script>

</head>

<body bgcolor=lavender>

<form action="sendmail.asp" method="POST">
<table cellpadding=0 cellspacing=0>
  <tr>
    <td style="width:60">From:</td>
    <td><input type=text name=from value="<%= Request.QueryString("from") %>" style="background-color:thistle; width:300"></td>
  </tr>
  <tr>
    <td>To:</td>
    <td><input type=text name=to value="<%= Request.QueryString("to") %>" style="background-color:thistle; width:300"></td>
  </tr>
  <tr>
    <td>CC:</td>
    <td><input type=text name=cc value="<%= Request.QueryString("cc") %>" style="background-color:thistle; width:300"></td>
  </tr>
  <tr>
    <td>BCC:</td>
    <td><input type=text name=bcc value="<%= Request.QueryString("bcc") %>" style="background-color:thistle; width:300"></td>
  </tr>
  <tr>
    <td>Subject:</td>
    <td><input type=text name=subject value="<%= Request.QueryString("subject") %>" style="background-color:thistle; width:300"></td>
  </tr>
</table>

<textarea name=msg style="background-color:thistle; width:530; height:105"></textarea>
<br>
<input type=button id=send value="Send" style="background-color:thistle">

</form>

</body>

</html>
