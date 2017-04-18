<%
On Error Resume Next
Session("oUIPublisher").PublishRequest Request, Response
Set Session("oUIPublisher") = Nothing
%>
