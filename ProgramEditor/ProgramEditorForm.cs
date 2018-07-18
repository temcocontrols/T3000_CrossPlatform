<!DOCTYPE html>
<html lang='en'>
<head>
<meta charset='utf-8'>
<meta content='GitLab Community Edition' name='description'>
<title>
t3000/ProgramEditor/ProgramEditorForm.cs at 04d1a0c6fd995bb0b730114d3ed87357ad1188aa - C programming / T3000 | 
GitLab
</title>
<link href="/assets/favicon-baaa14bade1248aa6165e9d34e7d83c0.ico" rel="shortcut icon" type="image/vnd.microsoft.icon" />
<link href="/assets/application-8afcf791d7afe64a25e5240b75fcf084.css" media="all" rel="stylesheet" />
<link href="/assets/print-1df3ea9b8ff148a6745321899e0cb213.css" media="print" rel="stylesheet" />
<script src="/assets/application-c8cd2dd87cbf8a023b21baf4d6996ac9.js"></script>
<meta content="authenticity_token" name="csrf-param" />
<meta content="zeFZ/KGipiN3yNnDwTN7rYVUizM6fL9wh++aiIjMx9U=" name="csrf-token" />
<script type="text/javascript">
//<![CDATA[
window.gon={};gon.default_issues_tracker="gitlab";gon.api_version="v3";gon.relative_url_root="";gon.default_avatar_url="https://phoenix.aimservices.tech:8082/assets/no_avatar-adffbfe10d45b20495cd2a9b88974150.png";gon.current_user_id=4;gon.api_token="pyGw9sAbr2CRk9BrPd2x";
//]]>
</script>
<meta name="viewport" content="width=device-width, initial-scale=1.0">




</head>

<body class='ui_mars project' data-page='projects:blob:show' data-project-id='36'>

<header class='navbar navbar-static-top navbar-gitlab'>
<div class='navbar-inner'>
<div class='container'>
<div class='app_logo'>
<span class='separator'></span>
<a class="home has_bottom_tooltip" href="/" title="Dashboard"><h1>GITLAB</h1>
</a><span class='separator'></span>
</div>
<h1 class='title'><span><a href="/groups/c-programming">C programming</a> / T3000</span></h1>
<button class='navbar-toggle' data-target='.navbar-collapse' data-toggle='collapse' type='button'>
<span class='sr-only'>Toggle navigation</span>
<i class='icon-reorder'></i>
</button>
<div class='navbar-collapse collapse'>
<ul class='nav navbar-nav'>
<li class='hidden-sm hidden-xs'>
<div class='search'>
<form accept-charset="UTF-8" action="/search" class="navbar-form pull-left" method="get"><div style="display:none"><input name="utf8" type="hidden" value="&#x2713;" /></div>
<input class="search-input" id="search" name="search" placeholder="Search in this project" type="search" />
<input id="group_id" name="group_id" type="hidden" />
<input id="project_id" name="project_id" type="hidden" value="36" />
<input id="search_code" name="search_code" type="hidden" value="true" />
<input id="repository_ref" name="repository_ref" type="hidden" value="04d1a0c6fd995bb0b730114d3ed87357ad1188aa" />

<div class='search-autocomplete-opts hide' data-autocomplete-path='/search/autocomplete' data-autocomplete-project-id='36' data-autocomplete-project-ref='04d1a0c6fd995bb0b730114d3ed87357ad1188aa'></div>
</form>

</div>

</li>
<li class='visible-sm visible-xs'>
<a class="has_bottom_tooltip" data-original-title="Search area" href="/search" title="Search"><i class='icon-search'></i>
</a></li>
<li>
<a class="has_bottom_tooltip" data-original-title="Help" href="/help" title="Help"><i class='icon-question-sign'></i>
</a></li>
<li>
<a class="has_bottom_tooltip" data-original-title="Public area" href="/public" title="Public area"><i class='icon-globe'></i>
</a></li>
<li>
<a class="has_bottom_tooltip" data-original-title="My snippets" href="/s/allgama" title="My snippets"><i class='icon-paste'></i>
</a></li>
<li>
<a class="has_bottom_tooltip" data-original-title="Admin area" href="/admin" title="Admin area"><i class='icon-cogs'></i>
</a></li>
<li>
<a class="has_bottom_tooltip" data-original-title="New project" href="/projects/new" title="New project"><i class='icon-plus'></i>
</a></li>
<li>
<a class="has_bottom_tooltip" data-original-title="Profile settings&quot;" href="/profile" title="Profile settings"><i class='icon-user'></i>
</a></li>
<li>
<a class="has_bottom_tooltip" data-method="delete" data-original-title="Logout" href="/users/sign_out" rel="nofollow" title="Logout"><i class='icon-signout'></i>
</a></li>
<li class='hidden-xs'>
<a class="profile-pic" href="/u/allgama" id="profile-pic"><img alt="User activity" src="https://phoenix.aimservices.tech:8082//uploads/user/avatar/4/logo_5.jpg" />
</a></li>
</ul>
</div>
</div>
</div>
</header>

<script>
  GitLab.GfmAutoComplete.dataSource = "/c-programming/t3000/autocomplete_sources?type=NilClass&type_id=04d1a0c6fd995bb0b730114d3ed87357ad1188aa%2FProgramEditor%2FProgramEditorForm.cs"
  GitLab.GfmAutoComplete.setup();
</script>

<div class='flash-container'>
</div>


<nav class='main-nav navbar-collapse collapse'>
<div class='container'><ul>
<li class="home"><a href="/c-programming/t3000" title="Project">Activity
</a></li><li class="active"><a href="/c-programming/t3000/tree/04d1a0c6fd995bb0b730114d3ed87357ad1188aa">Files</a>
</li><li class=""><a href="/c-programming/t3000/commits/04d1a0c6fd995bb0b730114d3ed87357ad1188aa">Commits</a>
</li><li class=""><a href="/c-programming/t3000/network/04d1a0c6fd995bb0b730114d3ed87357ad1188aa">Network</a>
</li><li class=""><a href="/c-programming/t3000/graphs/04d1a0c6fd995bb0b730114d3ed87357ad1188aa">Graphs</a>
</li><li class=""><a href="/c-programming/t3000/issues">Issues
<span class='count issue_counter'>0</span>
</a></li><li class=""><a href="/c-programming/t3000/merge_requests">Merge Requests
<span class='count merge_counter'>0</span>
</a></li><li class=""><a href="/c-programming/t3000/wikis/home">Wiki</a>
</li><li class=""><a class="stat-tab tab " href="/c-programming/t3000/edit">Settings
</a></li></ul>
</div>
</nav>
<div class='container'>
<div class='content'><div class='tree-ref-holder'>
<form accept-charset="UTF-8" action="/c-programming/t3000/refs/switch" class="project-refs-form" method="get"><div style="display:none"><input name="utf8" type="hidden" value="&#x2713;" /></div>
<select class="project-refs-select select2 select2-sm" id="ref" name="ref"><optgroup label="Branches"><option value="master">master</option></optgroup><optgroup label="Tags"><option value="v1.0_ISSUE1_BUG_FIXED">v1.0_ISSUE1_BUG_FIXED</option>
<option value="v1.0.1___EDITOR+PRG_FIXING">v1.0.1___EDITOR+PRG_FIXING</option>
<option value="PARSER_COMPLETE">PARSER_COMPLETE</option>
<option value="ISSUE3_BUG_FOUND">ISSUE3_BUG_FOUND</option>
<option value="API_CALLS_REMOVED">API_CALLS_REMOVED</option></optgroup><optgroup label="Commit"><option selected="selected" value="04d1a0c6fd995bb0b730114d3ed87357ad1188aa">04d1a0c6fd995bb0b730114d3ed87357ad1188aa</option></optgroup></select>
<input id="destination" name="destination" type="hidden" value="blob" />
<input id="path" name="path" type="hidden" value="ProgramEditor/ProgramEditorForm.cs" />
</form>


</div>
<div class='tree-holder' id='tree-holder'>
<ul class='breadcrumb repo-breadcrumb'>
<li>
<i class='icon-angle-right'></i>
<a href="/c-programming/t3000/tree/04d1a0c6fd995bb0b730114d3ed87357ad1188aa">t3000
</a></li>
<li>
<a href="/c-programming/t3000/tree/04d1a0c6fd995bb0b730114d3ed87357ad1188aa/ProgramEditor">ProgramEditor</a>
</li>
<li>
<a href="/c-programming/t3000/blob/04d1a0c6fd995bb0b730114d3ed87357ad1188aa/ProgramEditor/ProgramEditorForm.cs"><strong>
ProgramEditorForm.cs
</strong>
</a></li>
</ul>
<ul class='blob-commit-info bs-callout bs-callout-info hidden-xs'>
<li class='commit js-toggle-container'>
<div class='commit-row-title'>
<a class="commit_short_id" href="/c-programming/t3000/commit/04d1a0c6fd995bb0b730114d3ed87357ad1188aa">04d1a0c6f</a>
&nbsp;
<span class='str-truncated'>
<a class="commit-row-message" href="/c-programming/t3000/commit/04d1a0c6fd995bb0b730114d3ed87357ad1188aa">ControlPoints copy remastered. Also new form frmIdentifierInfo to display when C&hellip;</a>
<a class='text-expander js-toggle-button'>...</a>
</span>
<a class="pull-right" href="/c-programming/t3000/tree/04d1a0c6fd995bb0b730114d3ed87357ad1188aa">Browse Code »</a>
<div class='notes_count'>
</div>
</div>
<div class='commit-row-description js-toggle-content'>
<pre>&hellip;TRL+INS on ProgramEditorForm. Need previous selection of text on Editor. NOTE: Editor doesn&#39;t have the method to do so, but ProgramEditorForm does.</pre>
</div>
<div class='commit-row-info'>
<a class="commit-author-link has_tooltip" data-original-title="lruiz@aimservices.tech" href="/u/lruiz"><img alt="" class="avatar s16" src="https://phoenix.aimservices.tech:8082//uploads/user/avatar/10/LRUIZ.jpg" width="16" /> <span class="commit-author-name">Luis Danilo Ruiz Tórrez</span></a>
<div class='committed_ago'>
<time class='time_ago' data-placement='top' data-toggle='tooltip' datetime='2018-06-25T23:42:39Z' title='Jun 25, 2018 7:42pm'>2018-06-25 19:42:39 -0400</time>
<script>$('.time_ago').timeago().tooltip()</script>
 &nbsp;
</div>
</div>
</li>

</ul>
<div class='tree-content-holder' id='tree-content-holder'>
<article class='file-holder'>
<div class='file-title clearfix'>
<i class='icon-file'></i>
<span class='file_name'>
ProgramEditorForm.cs
<small>58.3 KB</small>
</span>
<span class='options hidden-xs'><div class='btn-group tree-btn-group'>
<span class='btn btn-small disabled'>edit</span>
<a class="btn btn-small" href="/c-programming/t3000/raw/04d1a0c6fd995bb0b730114d3ed87357ad1188aa/ProgramEditor/ProgramEditorForm.cs" target="_blank">raw</a>
<a class="btn btn-small" href="/c-programming/t3000/blame/04d1a0c6fd995bb0b730114d3ed87357ad1188aa/ProgramEditor/ProgramEditorForm.cs">blame</a>
<a class="btn btn-small" href="/c-programming/t3000/commits/04d1a0c6fd995bb0b730114d3ed87357ad1188aa/ProgramEditor/ProgramEditorForm.cs">history</a>
</div>
</span>
</div>
<div class='file-content code'>
<div class='highlighted-data white'>
<div class='line-numbers'>
<a href="#L1" id="L1" rel="#L1"><i class='icon-link'></i>
1
</a><a href="#L2" id="L2" rel="#L2"><i class='icon-link'></i>
2
</a><a href="#L3" id="L3" rel="#L3"><i class='icon-link'></i>
3
</a><a href="#L4" id="L4" rel="#L4"><i class='icon-link'></i>
4
</a><a href="#L5" id="L5" rel="#L5"><i class='icon-link'></i>
5
</a><a href="#L6" id="L6" rel="#L6"><i class='icon-link'></i>
6
</a><a href="#L7" id="L7" rel="#L7"><i class='icon-link'></i>
7
</a><a href="#L8" id="L8" rel="#L8"><i class='icon-link'></i>
8
</a><a href="#L9" id="L9" rel="#L9"><i class='icon-link'></i>
9
</a><a href="#L10" id="L10" rel="#L10"><i class='icon-link'></i>
10
</a><a href="#L11" id="L11" rel="#L11"><i class='icon-link'></i>
11
</a><a href="#L12" id="L12" rel="#L12"><i class='icon-link'></i>
12
</a><a href="#L13" id="L13" rel="#L13"><i class='icon-link'></i>
13
</a><a href="#L14" id="L14" rel="#L14"><i class='icon-link'></i>
14
</a><a href="#L15" id="L15" rel="#L15"><i class='icon-link'></i>
15
</a><a href="#L16" id="L16" rel="#L16"><i class='icon-link'></i>
16
</a><a href="#L17" id="L17" rel="#L17"><i class='icon-link'></i>
17
</a><a href="#L18" id="L18" rel="#L18"><i class='icon-link'></i>
18
</a><a href="#L19" id="L19" rel="#L19"><i class='icon-link'></i>
19
</a><a href="#L20" id="L20" rel="#L20"><i class='icon-link'></i>
20
</a><a href="#L21" id="L21" rel="#L21"><i class='icon-link'></i>
21
</a><a href="#L22" id="L22" rel="#L22"><i class='icon-link'></i>
22
</a><a href="#L23" id="L23" rel="#L23"><i class='icon-link'></i>
23
</a><a href="#L24" id="L24" rel="#L24"><i class='icon-link'></i>
24
</a><a href="#L25" id="L25" rel="#L25"><i class='icon-link'></i>
25
</a><a href="#L26" id="L26" rel="#L26"><i class='icon-link'></i>
26
</a><a href="#L27" id="L27" rel="#L27"><i class='icon-link'></i>
27
</a><a href="#L28" id="L28" rel="#L28"><i class='icon-link'></i>
28
</a><a href="#L29" id="L29" rel="#L29"><i class='icon-link'></i>
29
</a><a href="#L30" id="L30" rel="#L30"><i class='icon-link'></i>
30
</a><a href="#L31" id="L31" rel="#L31"><i class='icon-link'></i>
31
</a><a href="#L32" id="L32" rel="#L32"><i class='icon-link'></i>
32
</a><a href="#L33" id="L33" rel="#L33"><i class='icon-link'></i>
33
</a><a href="#L34" id="L34" rel="#L34"><i class='icon-link'></i>
34
</a><a href="#L35" id="L35" rel="#L35"><i class='icon-link'></i>
35
</a><a href="#L36" id="L36" rel="#L36"><i class='icon-link'></i>
36
</a><a href="#L37" id="L37" rel="#L37"><i class='icon-link'></i>
37
</a><a href="#L38" id="L38" rel="#L38"><i class='icon-link'></i>
38
</a><a href="#L39" id="L39" rel="#L39"><i class='icon-link'></i>
39
</a><a href="#L40" id="L40" rel="#L40"><i class='icon-link'></i>
40
</a><a href="#L41" id="L41" rel="#L41"><i class='icon-link'></i>
41
</a><a href="#L42" id="L42" rel="#L42"><i class='icon-link'></i>
42
</a><a href="#L43" id="L43" rel="#L43"><i class='icon-link'></i>
43
</a><a href="#L44" id="L44" rel="#L44"><i class='icon-link'></i>
44
</a><a href="#L45" id="L45" rel="#L45"><i class='icon-link'></i>
45
</a><a href="#L46" id="L46" rel="#L46"><i class='icon-link'></i>
46
</a><a href="#L47" id="L47" rel="#L47"><i class='icon-link'></i>
47
</a><a href="#L48" id="L48" rel="#L48"><i class='icon-link'></i>
48
</a><a href="#L49" id="L49" rel="#L49"><i class='icon-link'></i>
49
</a><a href="#L50" id="L50" rel="#L50"><i class='icon-link'></i>
50
</a><a href="#L51" id="L51" rel="#L51"><i class='icon-link'></i>
51
</a><a href="#L52" id="L52" rel="#L52"><i class='icon-link'></i>
52
</a><a href="#L53" id="L53" rel="#L53"><i class='icon-link'></i>
53
</a><a href="#L54" id="L54" rel="#L54"><i class='icon-link'></i>
54
</a><a href="#L55" id="L55" rel="#L55"><i class='icon-link'></i>
55
</a><a href="#L56" id="L56" rel="#L56"><i class='icon-link'></i>
56
</a><a href="#L57" id="L57" rel="#L57"><i class='icon-link'></i>
57
</a><a href="#L58" id="L58" rel="#L58"><i class='icon-link'></i>
58
</a><a href="#L59" id="L59" rel="#L59"><i class='icon-link'></i>
59
</a><a href="#L60" id="L60" rel="#L60"><i class='icon-link'></i>
60
</a><a href="#L61" id="L61" rel="#L61"><i class='icon-link'></i>
61
</a><a href="#L62" id="L62" rel="#L62"><i class='icon-link'></i>
62
</a><a href="#L63" id="L63" rel="#L63"><i class='icon-link'></i>
63
</a><a href="#L64" id="L64" rel="#L64"><i class='icon-link'></i>
64
</a><a href="#L65" id="L65" rel="#L65"><i class='icon-link'></i>
65
</a><a href="#L66" id="L66" rel="#L66"><i class='icon-link'></i>
66
</a><a href="#L67" id="L67" rel="#L67"><i class='icon-link'></i>
67
</a><a href="#L68" id="L68" rel="#L68"><i class='icon-link'></i>
68
</a><a href="#L69" id="L69" rel="#L69"><i class='icon-link'></i>
69
</a><a href="#L70" id="L70" rel="#L70"><i class='icon-link'></i>
70
</a><a href="#L71" id="L71" rel="#L71"><i class='icon-link'></i>
71
</a><a href="#L72" id="L72" rel="#L72"><i class='icon-link'></i>
72
</a><a href="#L73" id="L73" rel="#L73"><i class='icon-link'></i>
73
</a><a href="#L74" id="L74" rel="#L74"><i class='icon-link'></i>
74
</a><a href="#L75" id="L75" rel="#L75"><i class='icon-link'></i>
75
</a><a href="#L76" id="L76" rel="#L76"><i class='icon-link'></i>
76
</a><a href="#L77" id="L77" rel="#L77"><i class='icon-link'></i>
77
</a><a href="#L78" id="L78" rel="#L78"><i class='icon-link'></i>
78
</a><a href="#L79" id="L79" rel="#L79"><i class='icon-link'></i>
79
</a><a href="#L80" id="L80" rel="#L80"><i class='icon-link'></i>
80
</a><a href="#L81" id="L81" rel="#L81"><i class='icon-link'></i>
81
</a><a href="#L82" id="L82" rel="#L82"><i class='icon-link'></i>
82
</a><a href="#L83" id="L83" rel="#L83"><i class='icon-link'></i>
83
</a><a href="#L84" id="L84" rel="#L84"><i class='icon-link'></i>
84
</a><a href="#L85" id="L85" rel="#L85"><i class='icon-link'></i>
85
</a><a href="#L86" id="L86" rel="#L86"><i class='icon-link'></i>
86
</a><a href="#L87" id="L87" rel="#L87"><i class='icon-link'></i>
87
</a><a href="#L88" id="L88" rel="#L88"><i class='icon-link'></i>
88
</a><a href="#L89" id="L89" rel="#L89"><i class='icon-link'></i>
89
</a><a href="#L90" id="L90" rel="#L90"><i class='icon-link'></i>
90
</a><a href="#L91" id="L91" rel="#L91"><i class='icon-link'></i>
91
</a><a href="#L92" id="L92" rel="#L92"><i class='icon-link'></i>
92
</a><a href="#L93" id="L93" rel="#L93"><i class='icon-link'></i>
93
</a><a href="#L94" id="L94" rel="#L94"><i class='icon-link'></i>
94
</a><a href="#L95" id="L95" rel="#L95"><i class='icon-link'></i>
95
</a><a href="#L96" id="L96" rel="#L96"><i class='icon-link'></i>
96
</a><a href="#L97" id="L97" rel="#L97"><i class='icon-link'></i>
97
</a><a href="#L98" id="L98" rel="#L98"><i class='icon-link'></i>
98
</a><a href="#L99" id="L99" rel="#L99"><i class='icon-link'></i>
99
</a><a href="#L100" id="L100" rel="#L100"><i class='icon-link'></i>
100
</a><a href="#L101" id="L101" rel="#L101"><i class='icon-link'></i>
101
</a><a href="#L102" id="L102" rel="#L102"><i class='icon-link'></i>
102
</a><a href="#L103" id="L103" rel="#L103"><i class='icon-link'></i>
103
</a><a href="#L104" id="L104" rel="#L104"><i class='icon-link'></i>
104
</a><a href="#L105" id="L105" rel="#L105"><i class='icon-link'></i>
105
</a><a href="#L106" id="L106" rel="#L106"><i class='icon-link'></i>
106
</a><a href="#L107" id="L107" rel="#L107"><i class='icon-link'></i>
107
</a><a href="#L108" id="L108" rel="#L108"><i class='icon-link'></i>
108
</a><a href="#L109" id="L109" rel="#L109"><i class='icon-link'></i>
109
</a><a href="#L110" id="L110" rel="#L110"><i class='icon-link'></i>
110
</a><a href="#L111" id="L111" rel="#L111"><i class='icon-link'></i>
111
</a><a href="#L112" id="L112" rel="#L112"><i class='icon-link'></i>
112
</a><a href="#L113" id="L113" rel="#L113"><i class='icon-link'></i>
113
</a><a href="#L114" id="L114" rel="#L114"><i class='icon-link'></i>
114
</a><a href="#L115" id="L115" rel="#L115"><i class='icon-link'></i>
115
</a><a href="#L116" id="L116" rel="#L116"><i class='icon-link'></i>
116
</a><a href="#L117" id="L117" rel="#L117"><i class='icon-link'></i>
117
</a><a href="#L118" id="L118" rel="#L118"><i class='icon-link'></i>
118
</a><a href="#L119" id="L119" rel="#L119"><i class='icon-link'></i>
119
</a><a href="#L120" id="L120" rel="#L120"><i class='icon-link'></i>
120
</a><a href="#L121" id="L121" rel="#L121"><i class='icon-link'></i>
121
</a><a href="#L122" id="L122" rel="#L122"><i class='icon-link'></i>
122
</a><a href="#L123" id="L123" rel="#L123"><i class='icon-link'></i>
123
</a><a href="#L124" id="L124" rel="#L124"><i class='icon-link'></i>
124
</a><a href="#L125" id="L125" rel="#L125"><i class='icon-link'></i>
125
</a><a href="#L126" id="L126" rel="#L126"><i class='icon-link'></i>
126
</a><a href="#L127" id="L127" rel="#L127"><i class='icon-link'></i>
127
</a><a href="#L128" id="L128" rel="#L128"><i class='icon-link'></i>
128
</a><a href="#L129" id="L129" rel="#L129"><i class='icon-link'></i>
129
</a><a href="#L130" id="L130" rel="#L130"><i class='icon-link'></i>
130
</a><a href="#L131" id="L131" rel="#L131"><i class='icon-link'></i>
131
</a><a href="#L132" id="L132" rel="#L132"><i class='icon-link'></i>
132
</a><a href="#L133" id="L133" rel="#L133"><i class='icon-link'></i>
133
</a><a href="#L134" id="L134" rel="#L134"><i class='icon-link'></i>
134
</a><a href="#L135" id="L135" rel="#L135"><i class='icon-link'></i>
135
</a><a href="#L136" id="L136" rel="#L136"><i class='icon-link'></i>
136
</a><a href="#L137" id="L137" rel="#L137"><i class='icon-link'></i>
137
</a><a href="#L138" id="L138" rel="#L138"><i class='icon-link'></i>
138
</a><a href="#L139" id="L139" rel="#L139"><i class='icon-link'></i>
139
</a><a href="#L140" id="L140" rel="#L140"><i class='icon-link'></i>
140
</a><a href="#L141" id="L141" rel="#L141"><i class='icon-link'></i>
141
</a><a href="#L142" id="L142" rel="#L142"><i class='icon-link'></i>
142
</a><a href="#L143" id="L143" rel="#L143"><i class='icon-link'></i>
143
</a><a href="#L144" id="L144" rel="#L144"><i class='icon-link'></i>
144
</a><a href="#L145" id="L145" rel="#L145"><i class='icon-link'></i>
145
</a><a href="#L146" id="L146" rel="#L146"><i class='icon-link'></i>
146
</a><a href="#L147" id="L147" rel="#L147"><i class='icon-link'></i>
147
</a><a href="#L148" id="L148" rel="#L148"><i class='icon-link'></i>
148
</a><a href="#L149" id="L149" rel="#L149"><i class='icon-link'></i>
149
</a><a href="#L150" id="L150" rel="#L150"><i class='icon-link'></i>
150
</a><a href="#L151" id="L151" rel="#L151"><i class='icon-link'></i>
151
</a><a href="#L152" id="L152" rel="#L152"><i class='icon-link'></i>
152
</a><a href="#L153" id="L153" rel="#L153"><i class='icon-link'></i>
153
</a><a href="#L154" id="L154" rel="#L154"><i class='icon-link'></i>
154
</a><a href="#L155" id="L155" rel="#L155"><i class='icon-link'></i>
155
</a><a href="#L156" id="L156" rel="#L156"><i class='icon-link'></i>
156
</a><a href="#L157" id="L157" rel="#L157"><i class='icon-link'></i>
157
</a><a href="#L158" id="L158" rel="#L158"><i class='icon-link'></i>
158
</a><a href="#L159" id="L159" rel="#L159"><i class='icon-link'></i>
159
</a><a href="#L160" id="L160" rel="#L160"><i class='icon-link'></i>
160
</a><a href="#L161" id="L161" rel="#L161"><i class='icon-link'></i>
161
</a><a href="#L162" id="L162" rel="#L162"><i class='icon-link'></i>
162
</a><a href="#L163" id="L163" rel="#L163"><i class='icon-link'></i>
163
</a><a href="#L164" id="L164" rel="#L164"><i class='icon-link'></i>
164
</a><a href="#L165" id="L165" rel="#L165"><i class='icon-link'></i>
165
</a><a href="#L166" id="L166" rel="#L166"><i class='icon-link'></i>
166
</a><a href="#L167" id="L167" rel="#L167"><i class='icon-link'></i>
167
</a><a href="#L168" id="L168" rel="#L168"><i class='icon-link'></i>
168
</a><a href="#L169" id="L169" rel="#L169"><i class='icon-link'></i>
169
</a><a href="#L170" id="L170" rel="#L170"><i class='icon-link'></i>
170
</a><a href="#L171" id="L171" rel="#L171"><i class='icon-link'></i>
171
</a><a href="#L172" id="L172" rel="#L172"><i class='icon-link'></i>
172
</a><a href="#L173" id="L173" rel="#L173"><i class='icon-link'></i>
173
</a><a href="#L174" id="L174" rel="#L174"><i class='icon-link'></i>
174
</a><a href="#L175" id="L175" rel="#L175"><i class='icon-link'></i>
175
</a><a href="#L176" id="L176" rel="#L176"><i class='icon-link'></i>
176
</a><a href="#L177" id="L177" rel="#L177"><i class='icon-link'></i>
177
</a><a href="#L178" id="L178" rel="#L178"><i class='icon-link'></i>
178
</a><a href="#L179" id="L179" rel="#L179"><i class='icon-link'></i>
179
</a><a href="#L180" id="L180" rel="#L180"><i class='icon-link'></i>
180
</a><a href="#L181" id="L181" rel="#L181"><i class='icon-link'></i>
181
</a><a href="#L182" id="L182" rel="#L182"><i class='icon-link'></i>
182
</a><a href="#L183" id="L183" rel="#L183"><i class='icon-link'></i>
183
</a><a href="#L184" id="L184" rel="#L184"><i class='icon-link'></i>
184
</a><a href="#L185" id="L185" rel="#L185"><i class='icon-link'></i>
185
</a><a href="#L186" id="L186" rel="#L186"><i class='icon-link'></i>
186
</a><a href="#L187" id="L187" rel="#L187"><i class='icon-link'></i>
187
</a><a href="#L188" id="L188" rel="#L188"><i class='icon-link'></i>
188
</a><a href="#L189" id="L189" rel="#L189"><i class='icon-link'></i>
189
</a><a href="#L190" id="L190" rel="#L190"><i class='icon-link'></i>
190
</a><a href="#L191" id="L191" rel="#L191"><i class='icon-link'></i>
191
</a><a href="#L192" id="L192" rel="#L192"><i class='icon-link'></i>
192
</a><a href="#L193" id="L193" rel="#L193"><i class='icon-link'></i>
193
</a><a href="#L194" id="L194" rel="#L194"><i class='icon-link'></i>
194
</a><a href="#L195" id="L195" rel="#L195"><i class='icon-link'></i>
195
</a><a href="#L196" id="L196" rel="#L196"><i class='icon-link'></i>
196
</a><a href="#L197" id="L197" rel="#L197"><i class='icon-link'></i>
197
</a><a href="#L198" id="L198" rel="#L198"><i class='icon-link'></i>
198
</a><a href="#L199" id="L199" rel="#L199"><i class='icon-link'></i>
199
</a><a href="#L200" id="L200" rel="#L200"><i class='icon-link'></i>
200
</a><a href="#L201" id="L201" rel="#L201"><i class='icon-link'></i>
201
</a><a href="#L202" id="L202" rel="#L202"><i class='icon-link'></i>
202
</a><a href="#L203" id="L203" rel="#L203"><i class='icon-link'></i>
203
</a><a href="#L204" id="L204" rel="#L204"><i class='icon-link'></i>
204
</a><a href="#L205" id="L205" rel="#L205"><i class='icon-link'></i>
205
</a><a href="#L206" id="L206" rel="#L206"><i class='icon-link'></i>
206
</a><a href="#L207" id="L207" rel="#L207"><i class='icon-link'></i>
207
</a><a href="#L208" id="L208" rel="#L208"><i class='icon-link'></i>
208
</a><a href="#L209" id="L209" rel="#L209"><i class='icon-link'></i>
209
</a><a href="#L210" id="L210" rel="#L210"><i class='icon-link'></i>
210
</a><a href="#L211" id="L211" rel="#L211"><i class='icon-link'></i>
211
</a><a href="#L212" id="L212" rel="#L212"><i class='icon-link'></i>
212
</a><a href="#L213" id="L213" rel="#L213"><i class='icon-link'></i>
213
</a><a href="#L214" id="L214" rel="#L214"><i class='icon-link'></i>
214
</a><a href="#L215" id="L215" rel="#L215"><i class='icon-link'></i>
215
</a><a href="#L216" id="L216" rel="#L216"><i class='icon-link'></i>
216
</a><a href="#L217" id="L217" rel="#L217"><i class='icon-link'></i>
217
</a><a href="#L218" id="L218" rel="#L218"><i class='icon-link'></i>
218
</a><a href="#L219" id="L219" rel="#L219"><i class='icon-link'></i>
219
</a><a href="#L220" id="L220" rel="#L220"><i class='icon-link'></i>
220
</a><a href="#L221" id="L221" rel="#L221"><i class='icon-link'></i>
221
</a><a href="#L222" id="L222" rel="#L222"><i class='icon-link'></i>
222
</a><a href="#L223" id="L223" rel="#L223"><i class='icon-link'></i>
223
</a><a href="#L224" id="L224" rel="#L224"><i class='icon-link'></i>
224
</a><a href="#L225" id="L225" rel="#L225"><i class='icon-link'></i>
225
</a><a href="#L226" id="L226" rel="#L226"><i class='icon-link'></i>
226
</a><a href="#L227" id="L227" rel="#L227"><i class='icon-link'></i>
227
</a><a href="#L228" id="L228" rel="#L228"><i class='icon-link'></i>
228
</a><a href="#L229" id="L229" rel="#L229"><i class='icon-link'></i>
229
</a><a href="#L230" id="L230" rel="#L230"><i class='icon-link'></i>
230
</a><a href="#L231" id="L231" rel="#L231"><i class='icon-link'></i>
231
</a><a href="#L232" id="L232" rel="#L232"><i class='icon-link'></i>
232
</a><a href="#L233" id="L233" rel="#L233"><i class='icon-link'></i>
233
</a><a href="#L234" id="L234" rel="#L234"><i class='icon-link'></i>
234
</a><a href="#L235" id="L235" rel="#L235"><i class='icon-link'></i>
235
</a><a href="#L236" id="L236" rel="#L236"><i class='icon-link'></i>
236
</a><a href="#L237" id="L237" rel="#L237"><i class='icon-link'></i>
237
</a><a href="#L238" id="L238" rel="#L238"><i class='icon-link'></i>
238
</a><a href="#L239" id="L239" rel="#L239"><i class='icon-link'></i>
239
</a><a href="#L240" id="L240" rel="#L240"><i class='icon-link'></i>
240
</a><a href="#L241" id="L241" rel="#L241"><i class='icon-link'></i>
241
</a><a href="#L242" id="L242" rel="#L242"><i class='icon-link'></i>
242
</a><a href="#L243" id="L243" rel="#L243"><i class='icon-link'></i>
243
</a><a href="#L244" id="L244" rel="#L244"><i class='icon-link'></i>
244
</a><a href="#L245" id="L245" rel="#L245"><i class='icon-link'></i>
245
</a><a href="#L246" id="L246" rel="#L246"><i class='icon-link'></i>
246
</a><a href="#L247" id="L247" rel="#L247"><i class='icon-link'></i>
247
</a><a href="#L248" id="L248" rel="#L248"><i class='icon-link'></i>
248
</a><a href="#L249" id="L249" rel="#L249"><i class='icon-link'></i>
249
</a><a href="#L250" id="L250" rel="#L250"><i class='icon-link'></i>
250
</a><a href="#L251" id="L251" rel="#L251"><i class='icon-link'></i>
251
</a><a href="#L252" id="L252" rel="#L252"><i class='icon-link'></i>
252
</a><a href="#L253" id="L253" rel="#L253"><i class='icon-link'></i>
253
</a><a href="#L254" id="L254" rel="#L254"><i class='icon-link'></i>
254
</a><a href="#L255" id="L255" rel="#L255"><i class='icon-link'></i>
255
</a><a href="#L256" id="L256" rel="#L256"><i class='icon-link'></i>
256
</a><a href="#L257" id="L257" rel="#L257"><i class='icon-link'></i>
257
</a><a href="#L258" id="L258" rel="#L258"><i class='icon-link'></i>
258
</a><a href="#L259" id="L259" rel="#L259"><i class='icon-link'></i>
259
</a><a href="#L260" id="L260" rel="#L260"><i class='icon-link'></i>
260
</a><a href="#L261" id="L261" rel="#L261"><i class='icon-link'></i>
261
</a><a href="#L262" id="L262" rel="#L262"><i class='icon-link'></i>
262
</a><a href="#L263" id="L263" rel="#L263"><i class='icon-link'></i>
263
</a><a href="#L264" id="L264" rel="#L264"><i class='icon-link'></i>
264
</a><a href="#L265" id="L265" rel="#L265"><i class='icon-link'></i>
265
</a><a href="#L266" id="L266" rel="#L266"><i class='icon-link'></i>
266
</a><a href="#L267" id="L267" rel="#L267"><i class='icon-link'></i>
267
</a><a href="#L268" id="L268" rel="#L268"><i class='icon-link'></i>
268
</a><a href="#L269" id="L269" rel="#L269"><i class='icon-link'></i>
269
</a><a href="#L270" id="L270" rel="#L270"><i class='icon-link'></i>
270
</a><a href="#L271" id="L271" rel="#L271"><i class='icon-link'></i>
271
</a><a href="#L272" id="L272" rel="#L272"><i class='icon-link'></i>
272
</a><a href="#L273" id="L273" rel="#L273"><i class='icon-link'></i>
273
</a><a href="#L274" id="L274" rel="#L274"><i class='icon-link'></i>
274
</a><a href="#L275" id="L275" rel="#L275"><i class='icon-link'></i>
275
</a><a href="#L276" id="L276" rel="#L276"><i class='icon-link'></i>
276
</a><a href="#L277" id="L277" rel="#L277"><i class='icon-link'></i>
277
</a><a href="#L278" id="L278" rel="#L278"><i class='icon-link'></i>
278
</a><a href="#L279" id="L279" rel="#L279"><i class='icon-link'></i>
279
</a><a href="#L280" id="L280" rel="#L280"><i class='icon-link'></i>
280
</a><a href="#L281" id="L281" rel="#L281"><i class='icon-link'></i>
281
</a><a href="#L282" id="L282" rel="#L282"><i class='icon-link'></i>
282
</a><a href="#L283" id="L283" rel="#L283"><i class='icon-link'></i>
283
</a><a href="#L284" id="L284" rel="#L284"><i class='icon-link'></i>
284
</a><a href="#L285" id="L285" rel="#L285"><i class='icon-link'></i>
285
</a><a href="#L286" id="L286" rel="#L286"><i class='icon-link'></i>
286
</a><a href="#L287" id="L287" rel="#L287"><i class='icon-link'></i>
287
</a><a href="#L288" id="L288" rel="#L288"><i class='icon-link'></i>
288
</a><a href="#L289" id="L289" rel="#L289"><i class='icon-link'></i>
289
</a><a href="#L290" id="L290" rel="#L290"><i class='icon-link'></i>
290
</a><a href="#L291" id="L291" rel="#L291"><i class='icon-link'></i>
291
</a><a href="#L292" id="L292" rel="#L292"><i class='icon-link'></i>
292
</a><a href="#L293" id="L293" rel="#L293"><i class='icon-link'></i>
293
</a><a href="#L294" id="L294" rel="#L294"><i class='icon-link'></i>
294
</a><a href="#L295" id="L295" rel="#L295"><i class='icon-link'></i>
295
</a><a href="#L296" id="L296" rel="#L296"><i class='icon-link'></i>
296
</a><a href="#L297" id="L297" rel="#L297"><i class='icon-link'></i>
297
</a><a href="#L298" id="L298" rel="#L298"><i class='icon-link'></i>
298
</a><a href="#L299" id="L299" rel="#L299"><i class='icon-link'></i>
299
</a><a href="#L300" id="L300" rel="#L300"><i class='icon-link'></i>
300
</a><a href="#L301" id="L301" rel="#L301"><i class='icon-link'></i>
301
</a><a href="#L302" id="L302" rel="#L302"><i class='icon-link'></i>
302
</a><a href="#L303" id="L303" rel="#L303"><i class='icon-link'></i>
303
</a><a href="#L304" id="L304" rel="#L304"><i class='icon-link'></i>
304
</a><a href="#L305" id="L305" rel="#L305"><i class='icon-link'></i>
305
</a><a href="#L306" id="L306" rel="#L306"><i class='icon-link'></i>
306
</a><a href="#L307" id="L307" rel="#L307"><i class='icon-link'></i>
307
</a><a href="#L308" id="L308" rel="#L308"><i class='icon-link'></i>
308
</a><a href="#L309" id="L309" rel="#L309"><i class='icon-link'></i>
309
</a><a href="#L310" id="L310" rel="#L310"><i class='icon-link'></i>
310
</a><a href="#L311" id="L311" rel="#L311"><i class='icon-link'></i>
311
</a><a href="#L312" id="L312" rel="#L312"><i class='icon-link'></i>
312
</a><a href="#L313" id="L313" rel="#L313"><i class='icon-link'></i>
313
</a><a href="#L314" id="L314" rel="#L314"><i class='icon-link'></i>
314
</a><a href="#L315" id="L315" rel="#L315"><i class='icon-link'></i>
315
</a><a href="#L316" id="L316" rel="#L316"><i class='icon-link'></i>
316
</a><a href="#L317" id="L317" rel="#L317"><i class='icon-link'></i>
317
</a><a href="#L318" id="L318" rel="#L318"><i class='icon-link'></i>
318
</a><a href="#L319" id="L319" rel="#L319"><i class='icon-link'></i>
319
</a><a href="#L320" id="L320" rel="#L320"><i class='icon-link'></i>
320
</a><a href="#L321" id="L321" rel="#L321"><i class='icon-link'></i>
321
</a><a href="#L322" id="L322" rel="#L322"><i class='icon-link'></i>
322
</a><a href="#L323" id="L323" rel="#L323"><i class='icon-link'></i>
323
</a><a href="#L324" id="L324" rel="#L324"><i class='icon-link'></i>
324
</a><a href="#L325" id="L325" rel="#L325"><i class='icon-link'></i>
325
</a><a href="#L326" id="L326" rel="#L326"><i class='icon-link'></i>
326
</a><a href="#L327" id="L327" rel="#L327"><i class='icon-link'></i>
327
</a><a href="#L328" id="L328" rel="#L328"><i class='icon-link'></i>
328
</a><a href="#L329" id="L329" rel="#L329"><i class='icon-link'></i>
329
</a><a href="#L330" id="L330" rel="#L330"><i class='icon-link'></i>
330
</a><a href="#L331" id="L331" rel="#L331"><i class='icon-link'></i>
331
</a><a href="#L332" id="L332" rel="#L332"><i class='icon-link'></i>
332
</a><a href="#L333" id="L333" rel="#L333"><i class='icon-link'></i>
333
</a><a href="#L334" id="L334" rel="#L334"><i class='icon-link'></i>
334
</a><a href="#L335" id="L335" rel="#L335"><i class='icon-link'></i>
335
</a><a href="#L336" id="L336" rel="#L336"><i class='icon-link'></i>
336
</a><a href="#L337" id="L337" rel="#L337"><i class='icon-link'></i>
337
</a><a href="#L338" id="L338" rel="#L338"><i class='icon-link'></i>
338
</a><a href="#L339" id="L339" rel="#L339"><i class='icon-link'></i>
339
</a><a href="#L340" id="L340" rel="#L340"><i class='icon-link'></i>
340
</a><a href="#L341" id="L341" rel="#L341"><i class='icon-link'></i>
341
</a><a href="#L342" id="L342" rel="#L342"><i class='icon-link'></i>
342
</a><a href="#L343" id="L343" rel="#L343"><i class='icon-link'></i>
343
</a><a href="#L344" id="L344" rel="#L344"><i class='icon-link'></i>
344
</a><a href="#L345" id="L345" rel="#L345"><i class='icon-link'></i>
345
</a><a href="#L346" id="L346" rel="#L346"><i class='icon-link'></i>
346
</a><a href="#L347" id="L347" rel="#L347"><i class='icon-link'></i>
347
</a><a href="#L348" id="L348" rel="#L348"><i class='icon-link'></i>
348
</a><a href="#L349" id="L349" rel="#L349"><i class='icon-link'></i>
349
</a><a href="#L350" id="L350" rel="#L350"><i class='icon-link'></i>
350
</a><a href="#L351" id="L351" rel="#L351"><i class='icon-link'></i>
351
</a><a href="#L352" id="L352" rel="#L352"><i class='icon-link'></i>
352
</a><a href="#L353" id="L353" rel="#L353"><i class='icon-link'></i>
353
</a><a href="#L354" id="L354" rel="#L354"><i class='icon-link'></i>
354
</a><a href="#L355" id="L355" rel="#L355"><i class='icon-link'></i>
355
</a><a href="#L356" id="L356" rel="#L356"><i class='icon-link'></i>
356
</a><a href="#L357" id="L357" rel="#L357"><i class='icon-link'></i>
357
</a><a href="#L358" id="L358" rel="#L358"><i class='icon-link'></i>
358
</a><a href="#L359" id="L359" rel="#L359"><i class='icon-link'></i>
359
</a><a href="#L360" id="L360" rel="#L360"><i class='icon-link'></i>
360
</a><a href="#L361" id="L361" rel="#L361"><i class='icon-link'></i>
361
</a><a href="#L362" id="L362" rel="#L362"><i class='icon-link'></i>
362
</a><a href="#L363" id="L363" rel="#L363"><i class='icon-link'></i>
363
</a><a href="#L364" id="L364" rel="#L364"><i class='icon-link'></i>
364
</a><a href="#L365" id="L365" rel="#L365"><i class='icon-link'></i>
365
</a><a href="#L366" id="L366" rel="#L366"><i class='icon-link'></i>
366
</a><a href="#L367" id="L367" rel="#L367"><i class='icon-link'></i>
367
</a><a href="#L368" id="L368" rel="#L368"><i class='icon-link'></i>
368
</a><a href="#L369" id="L369" rel="#L369"><i class='icon-link'></i>
369
</a><a href="#L370" id="L370" rel="#L370"><i class='icon-link'></i>
370
</a><a href="#L371" id="L371" rel="#L371"><i class='icon-link'></i>
371
</a><a href="#L372" id="L372" rel="#L372"><i class='icon-link'></i>
372
</a><a href="#L373" id="L373" rel="#L373"><i class='icon-link'></i>
373
</a><a href="#L374" id="L374" rel="#L374"><i class='icon-link'></i>
374
</a><a href="#L375" id="L375" rel="#L375"><i class='icon-link'></i>
375
</a><a href="#L376" id="L376" rel="#L376"><i class='icon-link'></i>
376
</a><a href="#L377" id="L377" rel="#L377"><i class='icon-link'></i>
377
</a><a href="#L378" id="L378" rel="#L378"><i class='icon-link'></i>
378
</a><a href="#L379" id="L379" rel="#L379"><i class='icon-link'></i>
379
</a><a href="#L380" id="L380" rel="#L380"><i class='icon-link'></i>
380
</a><a href="#L381" id="L381" rel="#L381"><i class='icon-link'></i>
381
</a><a href="#L382" id="L382" rel="#L382"><i class='icon-link'></i>
382
</a><a href="#L383" id="L383" rel="#L383"><i class='icon-link'></i>
383
</a><a href="#L384" id="L384" rel="#L384"><i class='icon-link'></i>
384
</a><a href="#L385" id="L385" rel="#L385"><i class='icon-link'></i>
385
</a><a href="#L386" id="L386" rel="#L386"><i class='icon-link'></i>
386
</a><a href="#L387" id="L387" rel="#L387"><i class='icon-link'></i>
387
</a><a href="#L388" id="L388" rel="#L388"><i class='icon-link'></i>
388
</a><a href="#L389" id="L389" rel="#L389"><i class='icon-link'></i>
389
</a><a href="#L390" id="L390" rel="#L390"><i class='icon-link'></i>
390
</a><a href="#L391" id="L391" rel="#L391"><i class='icon-link'></i>
391
</a><a href="#L392" id="L392" rel="#L392"><i class='icon-link'></i>
392
</a><a href="#L393" id="L393" rel="#L393"><i class='icon-link'></i>
393
</a><a href="#L394" id="L394" rel="#L394"><i class='icon-link'></i>
394
</a><a href="#L395" id="L395" rel="#L395"><i class='icon-link'></i>
395
</a><a href="#L396" id="L396" rel="#L396"><i class='icon-link'></i>
396
</a><a href="#L397" id="L397" rel="#L397"><i class='icon-link'></i>
397
</a><a href="#L398" id="L398" rel="#L398"><i class='icon-link'></i>
398
</a><a href="#L399" id="L399" rel="#L399"><i class='icon-link'></i>
399
</a><a href="#L400" id="L400" rel="#L400"><i class='icon-link'></i>
400
</a><a href="#L401" id="L401" rel="#L401"><i class='icon-link'></i>
401
</a><a href="#L402" id="L402" rel="#L402"><i class='icon-link'></i>
402
</a><a href="#L403" id="L403" rel="#L403"><i class='icon-link'></i>
403
</a><a href="#L404" id="L404" rel="#L404"><i class='icon-link'></i>
404
</a><a href="#L405" id="L405" rel="#L405"><i class='icon-link'></i>
405
</a><a href="#L406" id="L406" rel="#L406"><i class='icon-link'></i>
406
</a><a href="#L407" id="L407" rel="#L407"><i class='icon-link'></i>
407
</a><a href="#L408" id="L408" rel="#L408"><i class='icon-link'></i>
408
</a><a href="#L409" id="L409" rel="#L409"><i class='icon-link'></i>
409
</a><a href="#L410" id="L410" rel="#L410"><i class='icon-link'></i>
410
</a><a href="#L411" id="L411" rel="#L411"><i class='icon-link'></i>
411
</a><a href="#L412" id="L412" rel="#L412"><i class='icon-link'></i>
412
</a><a href="#L413" id="L413" rel="#L413"><i class='icon-link'></i>
413
</a><a href="#L414" id="L414" rel="#L414"><i class='icon-link'></i>
414
</a><a href="#L415" id="L415" rel="#L415"><i class='icon-link'></i>
415
</a><a href="#L416" id="L416" rel="#L416"><i class='icon-link'></i>
416
</a><a href="#L417" id="L417" rel="#L417"><i class='icon-link'></i>
417
</a><a href="#L418" id="L418" rel="#L418"><i class='icon-link'></i>
418
</a><a href="#L419" id="L419" rel="#L419"><i class='icon-link'></i>
419
</a><a href="#L420" id="L420" rel="#L420"><i class='icon-link'></i>
420
</a><a href="#L421" id="L421" rel="#L421"><i class='icon-link'></i>
421
</a><a href="#L422" id="L422" rel="#L422"><i class='icon-link'></i>
422
</a><a href="#L423" id="L423" rel="#L423"><i class='icon-link'></i>
423
</a><a href="#L424" id="L424" rel="#L424"><i class='icon-link'></i>
424
</a><a href="#L425" id="L425" rel="#L425"><i class='icon-link'></i>
425
</a><a href="#L426" id="L426" rel="#L426"><i class='icon-link'></i>
426
</a><a href="#L427" id="L427" rel="#L427"><i class='icon-link'></i>
427
</a><a href="#L428" id="L428" rel="#L428"><i class='icon-link'></i>
428
</a><a href="#L429" id="L429" rel="#L429"><i class='icon-link'></i>
429
</a><a href="#L430" id="L430" rel="#L430"><i class='icon-link'></i>
430
</a><a href="#L431" id="L431" rel="#L431"><i class='icon-link'></i>
431
</a><a href="#L432" id="L432" rel="#L432"><i class='icon-link'></i>
432
</a><a href="#L433" id="L433" rel="#L433"><i class='icon-link'></i>
433
</a><a href="#L434" id="L434" rel="#L434"><i class='icon-link'></i>
434
</a><a href="#L435" id="L435" rel="#L435"><i class='icon-link'></i>
435
</a><a href="#L436" id="L436" rel="#L436"><i class='icon-link'></i>
436
</a><a href="#L437" id="L437" rel="#L437"><i class='icon-link'></i>
437
</a><a href="#L438" id="L438" rel="#L438"><i class='icon-link'></i>
438
</a><a href="#L439" id="L439" rel="#L439"><i class='icon-link'></i>
439
</a><a href="#L440" id="L440" rel="#L440"><i class='icon-link'></i>
440
</a><a href="#L441" id="L441" rel="#L441"><i class='icon-link'></i>
441
</a><a href="#L442" id="L442" rel="#L442"><i class='icon-link'></i>
442
</a><a href="#L443" id="L443" rel="#L443"><i class='icon-link'></i>
443
</a><a href="#L444" id="L444" rel="#L444"><i class='icon-link'></i>
444
</a><a href="#L445" id="L445" rel="#L445"><i class='icon-link'></i>
445
</a><a href="#L446" id="L446" rel="#L446"><i class='icon-link'></i>
446
</a><a href="#L447" id="L447" rel="#L447"><i class='icon-link'></i>
447
</a><a href="#L448" id="L448" rel="#L448"><i class='icon-link'></i>
448
</a><a href="#L449" id="L449" rel="#L449"><i class='icon-link'></i>
449
</a><a href="#L450" id="L450" rel="#L450"><i class='icon-link'></i>
450
</a><a href="#L451" id="L451" rel="#L451"><i class='icon-link'></i>
451
</a><a href="#L452" id="L452" rel="#L452"><i class='icon-link'></i>
452
</a><a href="#L453" id="L453" rel="#L453"><i class='icon-link'></i>
453
</a><a href="#L454" id="L454" rel="#L454"><i class='icon-link'></i>
454
</a><a href="#L455" id="L455" rel="#L455"><i class='icon-link'></i>
455
</a><a href="#L456" id="L456" rel="#L456"><i class='icon-link'></i>
456
</a><a href="#L457" id="L457" rel="#L457"><i class='icon-link'></i>
457
</a><a href="#L458" id="L458" rel="#L458"><i class='icon-link'></i>
458
</a><a href="#L459" id="L459" rel="#L459"><i class='icon-link'></i>
459
</a><a href="#L460" id="L460" rel="#L460"><i class='icon-link'></i>
460
</a><a href="#L461" id="L461" rel="#L461"><i class='icon-link'></i>
461
</a><a href="#L462" id="L462" rel="#L462"><i class='icon-link'></i>
462
</a><a href="#L463" id="L463" rel="#L463"><i class='icon-link'></i>
463
</a><a href="#L464" id="L464" rel="#L464"><i class='icon-link'></i>
464
</a><a href="#L465" id="L465" rel="#L465"><i class='icon-link'></i>
465
</a><a href="#L466" id="L466" rel="#L466"><i class='icon-link'></i>
466
</a><a href="#L467" id="L467" rel="#L467"><i class='icon-link'></i>
467
</a><a href="#L468" id="L468" rel="#L468"><i class='icon-link'></i>
468
</a><a href="#L469" id="L469" rel="#L469"><i class='icon-link'></i>
469
</a><a href="#L470" id="L470" rel="#L470"><i class='icon-link'></i>
470
</a><a href="#L471" id="L471" rel="#L471"><i class='icon-link'></i>
471
</a><a href="#L472" id="L472" rel="#L472"><i class='icon-link'></i>
472
</a><a href="#L473" id="L473" rel="#L473"><i class='icon-link'></i>
473
</a><a href="#L474" id="L474" rel="#L474"><i class='icon-link'></i>
474
</a><a href="#L475" id="L475" rel="#L475"><i class='icon-link'></i>
475
</a><a href="#L476" id="L476" rel="#L476"><i class='icon-link'></i>
476
</a><a href="#L477" id="L477" rel="#L477"><i class='icon-link'></i>
477
</a><a href="#L478" id="L478" rel="#L478"><i class='icon-link'></i>
478
</a><a href="#L479" id="L479" rel="#L479"><i class='icon-link'></i>
479
</a><a href="#L480" id="L480" rel="#L480"><i class='icon-link'></i>
480
</a><a href="#L481" id="L481" rel="#L481"><i class='icon-link'></i>
481
</a><a href="#L482" id="L482" rel="#L482"><i class='icon-link'></i>
482
</a><a href="#L483" id="L483" rel="#L483"><i class='icon-link'></i>
483
</a><a href="#L484" id="L484" rel="#L484"><i class='icon-link'></i>
484
</a><a href="#L485" id="L485" rel="#L485"><i class='icon-link'></i>
485
</a><a href="#L486" id="L486" rel="#L486"><i class='icon-link'></i>
486
</a><a href="#L487" id="L487" rel="#L487"><i class='icon-link'></i>
487
</a><a href="#L488" id="L488" rel="#L488"><i class='icon-link'></i>
488
</a><a href="#L489" id="L489" rel="#L489"><i class='icon-link'></i>
489
</a><a href="#L490" id="L490" rel="#L490"><i class='icon-link'></i>
490
</a><a href="#L491" id="L491" rel="#L491"><i class='icon-link'></i>
491
</a><a href="#L492" id="L492" rel="#L492"><i class='icon-link'></i>
492
</a><a href="#L493" id="L493" rel="#L493"><i class='icon-link'></i>
493
</a><a href="#L494" id="L494" rel="#L494"><i class='icon-link'></i>
494
</a><a href="#L495" id="L495" rel="#L495"><i class='icon-link'></i>
495
</a><a href="#L496" id="L496" rel="#L496"><i class='icon-link'></i>
496
</a><a href="#L497" id="L497" rel="#L497"><i class='icon-link'></i>
497
</a><a href="#L498" id="L498" rel="#L498"><i class='icon-link'></i>
498
</a><a href="#L499" id="L499" rel="#L499"><i class='icon-link'></i>
499
</a><a href="#L500" id="L500" rel="#L500"><i class='icon-link'></i>
500
</a><a href="#L501" id="L501" rel="#L501"><i class='icon-link'></i>
501
</a><a href="#L502" id="L502" rel="#L502"><i class='icon-link'></i>
502
</a><a href="#L503" id="L503" rel="#L503"><i class='icon-link'></i>
503
</a><a href="#L504" id="L504" rel="#L504"><i class='icon-link'></i>
504
</a><a href="#L505" id="L505" rel="#L505"><i class='icon-link'></i>
505
</a><a href="#L506" id="L506" rel="#L506"><i class='icon-link'></i>
506
</a><a href="#L507" id="L507" rel="#L507"><i class='icon-link'></i>
507
</a><a href="#L508" id="L508" rel="#L508"><i class='icon-link'></i>
508
</a><a href="#L509" id="L509" rel="#L509"><i class='icon-link'></i>
509
</a><a href="#L510" id="L510" rel="#L510"><i class='icon-link'></i>
510
</a><a href="#L511" id="L511" rel="#L511"><i class='icon-link'></i>
511
</a><a href="#L512" id="L512" rel="#L512"><i class='icon-link'></i>
512
</a><a href="#L513" id="L513" rel="#L513"><i class='icon-link'></i>
513
</a><a href="#L514" id="L514" rel="#L514"><i class='icon-link'></i>
514
</a><a href="#L515" id="L515" rel="#L515"><i class='icon-link'></i>
515
</a><a href="#L516" id="L516" rel="#L516"><i class='icon-link'></i>
516
</a><a href="#L517" id="L517" rel="#L517"><i class='icon-link'></i>
517
</a><a href="#L518" id="L518" rel="#L518"><i class='icon-link'></i>
518
</a><a href="#L519" id="L519" rel="#L519"><i class='icon-link'></i>
519
</a><a href="#L520" id="L520" rel="#L520"><i class='icon-link'></i>
520
</a><a href="#L521" id="L521" rel="#L521"><i class='icon-link'></i>
521
</a><a href="#L522" id="L522" rel="#L522"><i class='icon-link'></i>
522
</a><a href="#L523" id="L523" rel="#L523"><i class='icon-link'></i>
523
</a><a href="#L524" id="L524" rel="#L524"><i class='icon-link'></i>
524
</a><a href="#L525" id="L525" rel="#L525"><i class='icon-link'></i>
525
</a><a href="#L526" id="L526" rel="#L526"><i class='icon-link'></i>
526
</a><a href="#L527" id="L527" rel="#L527"><i class='icon-link'></i>
527
</a><a href="#L528" id="L528" rel="#L528"><i class='icon-link'></i>
528
</a><a href="#L529" id="L529" rel="#L529"><i class='icon-link'></i>
529
</a><a href="#L530" id="L530" rel="#L530"><i class='icon-link'></i>
530
</a><a href="#L531" id="L531" rel="#L531"><i class='icon-link'></i>
531
</a><a href="#L532" id="L532" rel="#L532"><i class='icon-link'></i>
532
</a><a href="#L533" id="L533" rel="#L533"><i class='icon-link'></i>
533
</a><a href="#L534" id="L534" rel="#L534"><i class='icon-link'></i>
534
</a><a href="#L535" id="L535" rel="#L535"><i class='icon-link'></i>
535
</a><a href="#L536" id="L536" rel="#L536"><i class='icon-link'></i>
536
</a><a href="#L537" id="L537" rel="#L537"><i class='icon-link'></i>
537
</a><a href="#L538" id="L538" rel="#L538"><i class='icon-link'></i>
538
</a><a href="#L539" id="L539" rel="#L539"><i class='icon-link'></i>
539
</a><a href="#L540" id="L540" rel="#L540"><i class='icon-link'></i>
540
</a><a href="#L541" id="L541" rel="#L541"><i class='icon-link'></i>
541
</a><a href="#L542" id="L542" rel="#L542"><i class='icon-link'></i>
542
</a><a href="#L543" id="L543" rel="#L543"><i class='icon-link'></i>
543
</a><a href="#L544" id="L544" rel="#L544"><i class='icon-link'></i>
544
</a><a href="#L545" id="L545" rel="#L545"><i class='icon-link'></i>
545
</a><a href="#L546" id="L546" rel="#L546"><i class='icon-link'></i>
546
</a><a href="#L547" id="L547" rel="#L547"><i class='icon-link'></i>
547
</a><a href="#L548" id="L548" rel="#L548"><i class='icon-link'></i>
548
</a><a href="#L549" id="L549" rel="#L549"><i class='icon-link'></i>
549
</a><a href="#L550" id="L550" rel="#L550"><i class='icon-link'></i>
550
</a><a href="#L551" id="L551" rel="#L551"><i class='icon-link'></i>
551
</a><a href="#L552" id="L552" rel="#L552"><i class='icon-link'></i>
552
</a><a href="#L553" id="L553" rel="#L553"><i class='icon-link'></i>
553
</a><a href="#L554" id="L554" rel="#L554"><i class='icon-link'></i>
554
</a><a href="#L555" id="L555" rel="#L555"><i class='icon-link'></i>
555
</a><a href="#L556" id="L556" rel="#L556"><i class='icon-link'></i>
556
</a><a href="#L557" id="L557" rel="#L557"><i class='icon-link'></i>
557
</a><a href="#L558" id="L558" rel="#L558"><i class='icon-link'></i>
558
</a><a href="#L559" id="L559" rel="#L559"><i class='icon-link'></i>
559
</a><a href="#L560" id="L560" rel="#L560"><i class='icon-link'></i>
560
</a><a href="#L561" id="L561" rel="#L561"><i class='icon-link'></i>
561
</a><a href="#L562" id="L562" rel="#L562"><i class='icon-link'></i>
562
</a><a href="#L563" id="L563" rel="#L563"><i class='icon-link'></i>
563
</a><a href="#L564" id="L564" rel="#L564"><i class='icon-link'></i>
564
</a><a href="#L565" id="L565" rel="#L565"><i class='icon-link'></i>
565
</a><a href="#L566" id="L566" rel="#L566"><i class='icon-link'></i>
566
</a><a href="#L567" id="L567" rel="#L567"><i class='icon-link'></i>
567
</a><a href="#L568" id="L568" rel="#L568"><i class='icon-link'></i>
568
</a><a href="#L569" id="L569" rel="#L569"><i class='icon-link'></i>
569
</a><a href="#L570" id="L570" rel="#L570"><i class='icon-link'></i>
570
</a><a href="#L571" id="L571" rel="#L571"><i class='icon-link'></i>
571
</a><a href="#L572" id="L572" rel="#L572"><i class='icon-link'></i>
572
</a><a href="#L573" id="L573" rel="#L573"><i class='icon-link'></i>
573
</a><a href="#L574" id="L574" rel="#L574"><i class='icon-link'></i>
574
</a><a href="#L575" id="L575" rel="#L575"><i class='icon-link'></i>
575
</a><a href="#L576" id="L576" rel="#L576"><i class='icon-link'></i>
576
</a><a href="#L577" id="L577" rel="#L577"><i class='icon-link'></i>
577
</a><a href="#L578" id="L578" rel="#L578"><i class='icon-link'></i>
578
</a><a href="#L579" id="L579" rel="#L579"><i class='icon-link'></i>
579
</a><a href="#L580" id="L580" rel="#L580"><i class='icon-link'></i>
580
</a><a href="#L581" id="L581" rel="#L581"><i class='icon-link'></i>
581
</a><a href="#L582" id="L582" rel="#L582"><i class='icon-link'></i>
582
</a><a href="#L583" id="L583" rel="#L583"><i class='icon-link'></i>
583
</a><a href="#L584" id="L584" rel="#L584"><i class='icon-link'></i>
584
</a><a href="#L585" id="L585" rel="#L585"><i class='icon-link'></i>
585
</a><a href="#L586" id="L586" rel="#L586"><i class='icon-link'></i>
586
</a><a href="#L587" id="L587" rel="#L587"><i class='icon-link'></i>
587
</a><a href="#L588" id="L588" rel="#L588"><i class='icon-link'></i>
588
</a><a href="#L589" id="L589" rel="#L589"><i class='icon-link'></i>
589
</a><a href="#L590" id="L590" rel="#L590"><i class='icon-link'></i>
590
</a><a href="#L591" id="L591" rel="#L591"><i class='icon-link'></i>
591
</a><a href="#L592" id="L592" rel="#L592"><i class='icon-link'></i>
592
</a><a href="#L593" id="L593" rel="#L593"><i class='icon-link'></i>
593
</a><a href="#L594" id="L594" rel="#L594"><i class='icon-link'></i>
594
</a><a href="#L595" id="L595" rel="#L595"><i class='icon-link'></i>
595
</a><a href="#L596" id="L596" rel="#L596"><i class='icon-link'></i>
596
</a><a href="#L597" id="L597" rel="#L597"><i class='icon-link'></i>
597
</a><a href="#L598" id="L598" rel="#L598"><i class='icon-link'></i>
598
</a><a href="#L599" id="L599" rel="#L599"><i class='icon-link'></i>
599
</a><a href="#L600" id="L600" rel="#L600"><i class='icon-link'></i>
600
</a><a href="#L601" id="L601" rel="#L601"><i class='icon-link'></i>
601
</a><a href="#L602" id="L602" rel="#L602"><i class='icon-link'></i>
602
</a><a href="#L603" id="L603" rel="#L603"><i class='icon-link'></i>
603
</a><a href="#L604" id="L604" rel="#L604"><i class='icon-link'></i>
604
</a><a href="#L605" id="L605" rel="#L605"><i class='icon-link'></i>
605
</a><a href="#L606" id="L606" rel="#L606"><i class='icon-link'></i>
606
</a><a href="#L607" id="L607" rel="#L607"><i class='icon-link'></i>
607
</a><a href="#L608" id="L608" rel="#L608"><i class='icon-link'></i>
608
</a><a href="#L609" id="L609" rel="#L609"><i class='icon-link'></i>
609
</a><a href="#L610" id="L610" rel="#L610"><i class='icon-link'></i>
610
</a><a href="#L611" id="L611" rel="#L611"><i class='icon-link'></i>
611
</a><a href="#L612" id="L612" rel="#L612"><i class='icon-link'></i>
612
</a><a href="#L613" id="L613" rel="#L613"><i class='icon-link'></i>
613
</a><a href="#L614" id="L614" rel="#L614"><i class='icon-link'></i>
614
</a><a href="#L615" id="L615" rel="#L615"><i class='icon-link'></i>
615
</a><a href="#L616" id="L616" rel="#L616"><i class='icon-link'></i>
616
</a><a href="#L617" id="L617" rel="#L617"><i class='icon-link'></i>
617
</a><a href="#L618" id="L618" rel="#L618"><i class='icon-link'></i>
618
</a><a href="#L619" id="L619" rel="#L619"><i class='icon-link'></i>
619
</a><a href="#L620" id="L620" rel="#L620"><i class='icon-link'></i>
620
</a><a href="#L621" id="L621" rel="#L621"><i class='icon-link'></i>
621
</a><a href="#L622" id="L622" rel="#L622"><i class='icon-link'></i>
622
</a><a href="#L623" id="L623" rel="#L623"><i class='icon-link'></i>
623
</a><a href="#L624" id="L624" rel="#L624"><i class='icon-link'></i>
624
</a><a href="#L625" id="L625" rel="#L625"><i class='icon-link'></i>
625
</a><a href="#L626" id="L626" rel="#L626"><i class='icon-link'></i>
626
</a><a href="#L627" id="L627" rel="#L627"><i class='icon-link'></i>
627
</a><a href="#L628" id="L628" rel="#L628"><i class='icon-link'></i>
628
</a><a href="#L629" id="L629" rel="#L629"><i class='icon-link'></i>
629
</a><a href="#L630" id="L630" rel="#L630"><i class='icon-link'></i>
630
</a><a href="#L631" id="L631" rel="#L631"><i class='icon-link'></i>
631
</a><a href="#L632" id="L632" rel="#L632"><i class='icon-link'></i>
632
</a><a href="#L633" id="L633" rel="#L633"><i class='icon-link'></i>
633
</a><a href="#L634" id="L634" rel="#L634"><i class='icon-link'></i>
634
</a><a href="#L635" id="L635" rel="#L635"><i class='icon-link'></i>
635
</a><a href="#L636" id="L636" rel="#L636"><i class='icon-link'></i>
636
</a><a href="#L637" id="L637" rel="#L637"><i class='icon-link'></i>
637
</a><a href="#L638" id="L638" rel="#L638"><i class='icon-link'></i>
638
</a><a href="#L639" id="L639" rel="#L639"><i class='icon-link'></i>
639
</a><a href="#L640" id="L640" rel="#L640"><i class='icon-link'></i>
640
</a><a href="#L641" id="L641" rel="#L641"><i class='icon-link'></i>
641
</a><a href="#L642" id="L642" rel="#L642"><i class='icon-link'></i>
642
</a><a href="#L643" id="L643" rel="#L643"><i class='icon-link'></i>
643
</a><a href="#L644" id="L644" rel="#L644"><i class='icon-link'></i>
644
</a><a href="#L645" id="L645" rel="#L645"><i class='icon-link'></i>
645
</a><a href="#L646" id="L646" rel="#L646"><i class='icon-link'></i>
646
</a><a href="#L647" id="L647" rel="#L647"><i class='icon-link'></i>
647
</a><a href="#L648" id="L648" rel="#L648"><i class='icon-link'></i>
648
</a><a href="#L649" id="L649" rel="#L649"><i class='icon-link'></i>
649
</a><a href="#L650" id="L650" rel="#L650"><i class='icon-link'></i>
650
</a><a href="#L651" id="L651" rel="#L651"><i class='icon-link'></i>
651
</a><a href="#L652" id="L652" rel="#L652"><i class='icon-link'></i>
652
</a><a href="#L653" id="L653" rel="#L653"><i class='icon-link'></i>
653
</a><a href="#L654" id="L654" rel="#L654"><i class='icon-link'></i>
654
</a><a href="#L655" id="L655" rel="#L655"><i class='icon-link'></i>
655
</a><a href="#L656" id="L656" rel="#L656"><i class='icon-link'></i>
656
</a><a href="#L657" id="L657" rel="#L657"><i class='icon-link'></i>
657
</a><a href="#L658" id="L658" rel="#L658"><i class='icon-link'></i>
658
</a><a href="#L659" id="L659" rel="#L659"><i class='icon-link'></i>
659
</a><a href="#L660" id="L660" rel="#L660"><i class='icon-link'></i>
660
</a><a href="#L661" id="L661" rel="#L661"><i class='icon-link'></i>
661
</a><a href="#L662" id="L662" rel="#L662"><i class='icon-link'></i>
662
</a><a href="#L663" id="L663" rel="#L663"><i class='icon-link'></i>
663
</a><a href="#L664" id="L664" rel="#L664"><i class='icon-link'></i>
664
</a><a href="#L665" id="L665" rel="#L665"><i class='icon-link'></i>
665
</a><a href="#L666" id="L666" rel="#L666"><i class='icon-link'></i>
666
</a><a href="#L667" id="L667" rel="#L667"><i class='icon-link'></i>
667
</a><a href="#L668" id="L668" rel="#L668"><i class='icon-link'></i>
668
</a><a href="#L669" id="L669" rel="#L669"><i class='icon-link'></i>
669
</a><a href="#L670" id="L670" rel="#L670"><i class='icon-link'></i>
670
</a><a href="#L671" id="L671" rel="#L671"><i class='icon-link'></i>
671
</a><a href="#L672" id="L672" rel="#L672"><i class='icon-link'></i>
672
</a><a href="#L673" id="L673" rel="#L673"><i class='icon-link'></i>
673
</a><a href="#L674" id="L674" rel="#L674"><i class='icon-link'></i>
674
</a><a href="#L675" id="L675" rel="#L675"><i class='icon-link'></i>
675
</a><a href="#L676" id="L676" rel="#L676"><i class='icon-link'></i>
676
</a><a href="#L677" id="L677" rel="#L677"><i class='icon-link'></i>
677
</a><a href="#L678" id="L678" rel="#L678"><i class='icon-link'></i>
678
</a><a href="#L679" id="L679" rel="#L679"><i class='icon-link'></i>
679
</a><a href="#L680" id="L680" rel="#L680"><i class='icon-link'></i>
680
</a><a href="#L681" id="L681" rel="#L681"><i class='icon-link'></i>
681
</a><a href="#L682" id="L682" rel="#L682"><i class='icon-link'></i>
682
</a><a href="#L683" id="L683" rel="#L683"><i class='icon-link'></i>
683
</a><a href="#L684" id="L684" rel="#L684"><i class='icon-link'></i>
684
</a><a href="#L685" id="L685" rel="#L685"><i class='icon-link'></i>
685
</a><a href="#L686" id="L686" rel="#L686"><i class='icon-link'></i>
686
</a><a href="#L687" id="L687" rel="#L687"><i class='icon-link'></i>
687
</a><a href="#L688" id="L688" rel="#L688"><i class='icon-link'></i>
688
</a><a href="#L689" id="L689" rel="#L689"><i class='icon-link'></i>
689
</a><a href="#L690" id="L690" rel="#L690"><i class='icon-link'></i>
690
</a><a href="#L691" id="L691" rel="#L691"><i class='icon-link'></i>
691
</a><a href="#L692" id="L692" rel="#L692"><i class='icon-link'></i>
692
</a><a href="#L693" id="L693" rel="#L693"><i class='icon-link'></i>
693
</a><a href="#L694" id="L694" rel="#L694"><i class='icon-link'></i>
694
</a><a href="#L695" id="L695" rel="#L695"><i class='icon-link'></i>
695
</a><a href="#L696" id="L696" rel="#L696"><i class='icon-link'></i>
696
</a><a href="#L697" id="L697" rel="#L697"><i class='icon-link'></i>
697
</a><a href="#L698" id="L698" rel="#L698"><i class='icon-link'></i>
698
</a><a href="#L699" id="L699" rel="#L699"><i class='icon-link'></i>
699
</a><a href="#L700" id="L700" rel="#L700"><i class='icon-link'></i>
700
</a><a href="#L701" id="L701" rel="#L701"><i class='icon-link'></i>
701
</a><a href="#L702" id="L702" rel="#L702"><i class='icon-link'></i>
702
</a><a href="#L703" id="L703" rel="#L703"><i class='icon-link'></i>
703
</a><a href="#L704" id="L704" rel="#L704"><i class='icon-link'></i>
704
</a><a href="#L705" id="L705" rel="#L705"><i class='icon-link'></i>
705
</a><a href="#L706" id="L706" rel="#L706"><i class='icon-link'></i>
706
</a><a href="#L707" id="L707" rel="#L707"><i class='icon-link'></i>
707
</a><a href="#L708" id="L708" rel="#L708"><i class='icon-link'></i>
708
</a><a href="#L709" id="L709" rel="#L709"><i class='icon-link'></i>
709
</a><a href="#L710" id="L710" rel="#L710"><i class='icon-link'></i>
710
</a><a href="#L711" id="L711" rel="#L711"><i class='icon-link'></i>
711
</a><a href="#L712" id="L712" rel="#L712"><i class='icon-link'></i>
712
</a><a href="#L713" id="L713" rel="#L713"><i class='icon-link'></i>
713
</a><a href="#L714" id="L714" rel="#L714"><i class='icon-link'></i>
714
</a><a href="#L715" id="L715" rel="#L715"><i class='icon-link'></i>
715
</a><a href="#L716" id="L716" rel="#L716"><i class='icon-link'></i>
716
</a><a href="#L717" id="L717" rel="#L717"><i class='icon-link'></i>
717
</a><a href="#L718" id="L718" rel="#L718"><i class='icon-link'></i>
718
</a><a href="#L719" id="L719" rel="#L719"><i class='icon-link'></i>
719
</a><a href="#L720" id="L720" rel="#L720"><i class='icon-link'></i>
720
</a><a href="#L721" id="L721" rel="#L721"><i class='icon-link'></i>
721
</a><a href="#L722" id="L722" rel="#L722"><i class='icon-link'></i>
722
</a><a href="#L723" id="L723" rel="#L723"><i class='icon-link'></i>
723
</a><a href="#L724" id="L724" rel="#L724"><i class='icon-link'></i>
724
</a><a href="#L725" id="L725" rel="#L725"><i class='icon-link'></i>
725
</a><a href="#L726" id="L726" rel="#L726"><i class='icon-link'></i>
726
</a><a href="#L727" id="L727" rel="#L727"><i class='icon-link'></i>
727
</a><a href="#L728" id="L728" rel="#L728"><i class='icon-link'></i>
728
</a><a href="#L729" id="L729" rel="#L729"><i class='icon-link'></i>
729
</a><a href="#L730" id="L730" rel="#L730"><i class='icon-link'></i>
730
</a><a href="#L731" id="L731" rel="#L731"><i class='icon-link'></i>
731
</a><a href="#L732" id="L732" rel="#L732"><i class='icon-link'></i>
732
</a><a href="#L733" id="L733" rel="#L733"><i class='icon-link'></i>
733
</a><a href="#L734" id="L734" rel="#L734"><i class='icon-link'></i>
734
</a><a href="#L735" id="L735" rel="#L735"><i class='icon-link'></i>
735
</a><a href="#L736" id="L736" rel="#L736"><i class='icon-link'></i>
736
</a><a href="#L737" id="L737" rel="#L737"><i class='icon-link'></i>
737
</a><a href="#L738" id="L738" rel="#L738"><i class='icon-link'></i>
738
</a><a href="#L739" id="L739" rel="#L739"><i class='icon-link'></i>
739
</a><a href="#L740" id="L740" rel="#L740"><i class='icon-link'></i>
740
</a><a href="#L741" id="L741" rel="#L741"><i class='icon-link'></i>
741
</a><a href="#L742" id="L742" rel="#L742"><i class='icon-link'></i>
742
</a><a href="#L743" id="L743" rel="#L743"><i class='icon-link'></i>
743
</a><a href="#L744" id="L744" rel="#L744"><i class='icon-link'></i>
744
</a><a href="#L745" id="L745" rel="#L745"><i class='icon-link'></i>
745
</a><a href="#L746" id="L746" rel="#L746"><i class='icon-link'></i>
746
</a><a href="#L747" id="L747" rel="#L747"><i class='icon-link'></i>
747
</a><a href="#L748" id="L748" rel="#L748"><i class='icon-link'></i>
748
</a><a href="#L749" id="L749" rel="#L749"><i class='icon-link'></i>
749
</a><a href="#L750" id="L750" rel="#L750"><i class='icon-link'></i>
750
</a><a href="#L751" id="L751" rel="#L751"><i class='icon-link'></i>
751
</a><a href="#L752" id="L752" rel="#L752"><i class='icon-link'></i>
752
</a><a href="#L753" id="L753" rel="#L753"><i class='icon-link'></i>
753
</a><a href="#L754" id="L754" rel="#L754"><i class='icon-link'></i>
754
</a><a href="#L755" id="L755" rel="#L755"><i class='icon-link'></i>
755
</a><a href="#L756" id="L756" rel="#L756"><i class='icon-link'></i>
756
</a><a href="#L757" id="L757" rel="#L757"><i class='icon-link'></i>
757
</a><a href="#L758" id="L758" rel="#L758"><i class='icon-link'></i>
758
</a><a href="#L759" id="L759" rel="#L759"><i class='icon-link'></i>
759
</a><a href="#L760" id="L760" rel="#L760"><i class='icon-link'></i>
760
</a><a href="#L761" id="L761" rel="#L761"><i class='icon-link'></i>
761
</a><a href="#L762" id="L762" rel="#L762"><i class='icon-link'></i>
762
</a><a href="#L763" id="L763" rel="#L763"><i class='icon-link'></i>
763
</a><a href="#L764" id="L764" rel="#L764"><i class='icon-link'></i>
764
</a><a href="#L765" id="L765" rel="#L765"><i class='icon-link'></i>
765
</a><a href="#L766" id="L766" rel="#L766"><i class='icon-link'></i>
766
</a><a href="#L767" id="L767" rel="#L767"><i class='icon-link'></i>
767
</a><a href="#L768" id="L768" rel="#L768"><i class='icon-link'></i>
768
</a><a href="#L769" id="L769" rel="#L769"><i class='icon-link'></i>
769
</a><a href="#L770" id="L770" rel="#L770"><i class='icon-link'></i>
770
</a><a href="#L771" id="L771" rel="#L771"><i class='icon-link'></i>
771
</a><a href="#L772" id="L772" rel="#L772"><i class='icon-link'></i>
772
</a><a href="#L773" id="L773" rel="#L773"><i class='icon-link'></i>
773
</a><a href="#L774" id="L774" rel="#L774"><i class='icon-link'></i>
774
</a><a href="#L775" id="L775" rel="#L775"><i class='icon-link'></i>
775
</a><a href="#L776" id="L776" rel="#L776"><i class='icon-link'></i>
776
</a><a href="#L777" id="L777" rel="#L777"><i class='icon-link'></i>
777
</a><a href="#L778" id="L778" rel="#L778"><i class='icon-link'></i>
778
</a><a href="#L779" id="L779" rel="#L779"><i class='icon-link'></i>
779
</a><a href="#L780" id="L780" rel="#L780"><i class='icon-link'></i>
780
</a><a href="#L781" id="L781" rel="#L781"><i class='icon-link'></i>
781
</a><a href="#L782" id="L782" rel="#L782"><i class='icon-link'></i>
782
</a><a href="#L783" id="L783" rel="#L783"><i class='icon-link'></i>
783
</a><a href="#L784" id="L784" rel="#L784"><i class='icon-link'></i>
784
</a><a href="#L785" id="L785" rel="#L785"><i class='icon-link'></i>
785
</a><a href="#L786" id="L786" rel="#L786"><i class='icon-link'></i>
786
</a><a href="#L787" id="L787" rel="#L787"><i class='icon-link'></i>
787
</a><a href="#L788" id="L788" rel="#L788"><i class='icon-link'></i>
788
</a><a href="#L789" id="L789" rel="#L789"><i class='icon-link'></i>
789
</a><a href="#L790" id="L790" rel="#L790"><i class='icon-link'></i>
790
</a><a href="#L791" id="L791" rel="#L791"><i class='icon-link'></i>
791
</a><a href="#L792" id="L792" rel="#L792"><i class='icon-link'></i>
792
</a><a href="#L793" id="L793" rel="#L793"><i class='icon-link'></i>
793
</a><a href="#L794" id="L794" rel="#L794"><i class='icon-link'></i>
794
</a><a href="#L795" id="L795" rel="#L795"><i class='icon-link'></i>
795
</a><a href="#L796" id="L796" rel="#L796"><i class='icon-link'></i>
796
</a><a href="#L797" id="L797" rel="#L797"><i class='icon-link'></i>
797
</a><a href="#L798" id="L798" rel="#L798"><i class='icon-link'></i>
798
</a><a href="#L799" id="L799" rel="#L799"><i class='icon-link'></i>
799
</a><a href="#L800" id="L800" rel="#L800"><i class='icon-link'></i>
800
</a><a href="#L801" id="L801" rel="#L801"><i class='icon-link'></i>
801
</a><a href="#L802" id="L802" rel="#L802"><i class='icon-link'></i>
802
</a><a href="#L803" id="L803" rel="#L803"><i class='icon-link'></i>
803
</a><a href="#L804" id="L804" rel="#L804"><i class='icon-link'></i>
804
</a><a href="#L805" id="L805" rel="#L805"><i class='icon-link'></i>
805
</a><a href="#L806" id="L806" rel="#L806"><i class='icon-link'></i>
806
</a><a href="#L807" id="L807" rel="#L807"><i class='icon-link'></i>
807
</a><a href="#L808" id="L808" rel="#L808"><i class='icon-link'></i>
808
</a><a href="#L809" id="L809" rel="#L809"><i class='icon-link'></i>
809
</a><a href="#L810" id="L810" rel="#L810"><i class='icon-link'></i>
810
</a><a href="#L811" id="L811" rel="#L811"><i class='icon-link'></i>
811
</a><a href="#L812" id="L812" rel="#L812"><i class='icon-link'></i>
812
</a><a href="#L813" id="L813" rel="#L813"><i class='icon-link'></i>
813
</a><a href="#L814" id="L814" rel="#L814"><i class='icon-link'></i>
814
</a><a href="#L815" id="L815" rel="#L815"><i class='icon-link'></i>
815
</a><a href="#L816" id="L816" rel="#L816"><i class='icon-link'></i>
816
</a><a href="#L817" id="L817" rel="#L817"><i class='icon-link'></i>
817
</a><a href="#L818" id="L818" rel="#L818"><i class='icon-link'></i>
818
</a><a href="#L819" id="L819" rel="#L819"><i class='icon-link'></i>
819
</a><a href="#L820" id="L820" rel="#L820"><i class='icon-link'></i>
820
</a><a href="#L821" id="L821" rel="#L821"><i class='icon-link'></i>
821
</a><a href="#L822" id="L822" rel="#L822"><i class='icon-link'></i>
822
</a><a href="#L823" id="L823" rel="#L823"><i class='icon-link'></i>
823
</a><a href="#L824" id="L824" rel="#L824"><i class='icon-link'></i>
824
</a><a href="#L825" id="L825" rel="#L825"><i class='icon-link'></i>
825
</a><a href="#L826" id="L826" rel="#L826"><i class='icon-link'></i>
826
</a><a href="#L827" id="L827" rel="#L827"><i class='icon-link'></i>
827
</a><a href="#L828" id="L828" rel="#L828"><i class='icon-link'></i>
828
</a><a href="#L829" id="L829" rel="#L829"><i class='icon-link'></i>
829
</a><a href="#L830" id="L830" rel="#L830"><i class='icon-link'></i>
830
</a><a href="#L831" id="L831" rel="#L831"><i class='icon-link'></i>
831
</a><a href="#L832" id="L832" rel="#L832"><i class='icon-link'></i>
832
</a><a href="#L833" id="L833" rel="#L833"><i class='icon-link'></i>
833
</a><a href="#L834" id="L834" rel="#L834"><i class='icon-link'></i>
834
</a><a href="#L835" id="L835" rel="#L835"><i class='icon-link'></i>
835
</a><a href="#L836" id="L836" rel="#L836"><i class='icon-link'></i>
836
</a><a href="#L837" id="L837" rel="#L837"><i class='icon-link'></i>
837
</a><a href="#L838" id="L838" rel="#L838"><i class='icon-link'></i>
838
</a><a href="#L839" id="L839" rel="#L839"><i class='icon-link'></i>
839
</a><a href="#L840" id="L840" rel="#L840"><i class='icon-link'></i>
840
</a><a href="#L841" id="L841" rel="#L841"><i class='icon-link'></i>
841
</a><a href="#L842" id="L842" rel="#L842"><i class='icon-link'></i>
842
</a><a href="#L843" id="L843" rel="#L843"><i class='icon-link'></i>
843
</a><a href="#L844" id="L844" rel="#L844"><i class='icon-link'></i>
844
</a><a href="#L845" id="L845" rel="#L845"><i class='icon-link'></i>
845
</a><a href="#L846" id="L846" rel="#L846"><i class='icon-link'></i>
846
</a><a href="#L847" id="L847" rel="#L847"><i class='icon-link'></i>
847
</a><a href="#L848" id="L848" rel="#L848"><i class='icon-link'></i>
848
</a><a href="#L849" id="L849" rel="#L849"><i class='icon-link'></i>
849
</a><a href="#L850" id="L850" rel="#L850"><i class='icon-link'></i>
850
</a><a href="#L851" id="L851" rel="#L851"><i class='icon-link'></i>
851
</a><a href="#L852" id="L852" rel="#L852"><i class='icon-link'></i>
852
</a><a href="#L853" id="L853" rel="#L853"><i class='icon-link'></i>
853
</a><a href="#L854" id="L854" rel="#L854"><i class='icon-link'></i>
854
</a><a href="#L855" id="L855" rel="#L855"><i class='icon-link'></i>
855
</a><a href="#L856" id="L856" rel="#L856"><i class='icon-link'></i>
856
</a><a href="#L857" id="L857" rel="#L857"><i class='icon-link'></i>
857
</a><a href="#L858" id="L858" rel="#L858"><i class='icon-link'></i>
858
</a><a href="#L859" id="L859" rel="#L859"><i class='icon-link'></i>
859
</a><a href="#L860" id="L860" rel="#L860"><i class='icon-link'></i>
860
</a><a href="#L861" id="L861" rel="#L861"><i class='icon-link'></i>
861
</a><a href="#L862" id="L862" rel="#L862"><i class='icon-link'></i>
862
</a><a href="#L863" id="L863" rel="#L863"><i class='icon-link'></i>
863
</a><a href="#L864" id="L864" rel="#L864"><i class='icon-link'></i>
864
</a><a href="#L865" id="L865" rel="#L865"><i class='icon-link'></i>
865
</a><a href="#L866" id="L866" rel="#L866"><i class='icon-link'></i>
866
</a><a href="#L867" id="L867" rel="#L867"><i class='icon-link'></i>
867
</a><a href="#L868" id="L868" rel="#L868"><i class='icon-link'></i>
868
</a><a href="#L869" id="L869" rel="#L869"><i class='icon-link'></i>
869
</a><a href="#L870" id="L870" rel="#L870"><i class='icon-link'></i>
870
</a><a href="#L871" id="L871" rel="#L871"><i class='icon-link'></i>
871
</a><a href="#L872" id="L872" rel="#L872"><i class='icon-link'></i>
872
</a><a href="#L873" id="L873" rel="#L873"><i class='icon-link'></i>
873
</a><a href="#L874" id="L874" rel="#L874"><i class='icon-link'></i>
874
</a><a href="#L875" id="L875" rel="#L875"><i class='icon-link'></i>
875
</a><a href="#L876" id="L876" rel="#L876"><i class='icon-link'></i>
876
</a><a href="#L877" id="L877" rel="#L877"><i class='icon-link'></i>
877
</a><a href="#L878" id="L878" rel="#L878"><i class='icon-link'></i>
878
</a><a href="#L879" id="L879" rel="#L879"><i class='icon-link'></i>
879
</a><a href="#L880" id="L880" rel="#L880"><i class='icon-link'></i>
880
</a><a href="#L881" id="L881" rel="#L881"><i class='icon-link'></i>
881
</a><a href="#L882" id="L882" rel="#L882"><i class='icon-link'></i>
882
</a><a href="#L883" id="L883" rel="#L883"><i class='icon-link'></i>
883
</a><a href="#L884" id="L884" rel="#L884"><i class='icon-link'></i>
884
</a><a href="#L885" id="L885" rel="#L885"><i class='icon-link'></i>
885
</a><a href="#L886" id="L886" rel="#L886"><i class='icon-link'></i>
886
</a><a href="#L887" id="L887" rel="#L887"><i class='icon-link'></i>
887
</a><a href="#L888" id="L888" rel="#L888"><i class='icon-link'></i>
888
</a><a href="#L889" id="L889" rel="#L889"><i class='icon-link'></i>
889
</a><a href="#L890" id="L890" rel="#L890"><i class='icon-link'></i>
890
</a><a href="#L891" id="L891" rel="#L891"><i class='icon-link'></i>
891
</a><a href="#L892" id="L892" rel="#L892"><i class='icon-link'></i>
892
</a><a href="#L893" id="L893" rel="#L893"><i class='icon-link'></i>
893
</a><a href="#L894" id="L894" rel="#L894"><i class='icon-link'></i>
894
</a><a href="#L895" id="L895" rel="#L895"><i class='icon-link'></i>
895
</a><a href="#L896" id="L896" rel="#L896"><i class='icon-link'></i>
896
</a><a href="#L897" id="L897" rel="#L897"><i class='icon-link'></i>
897
</a><a href="#L898" id="L898" rel="#L898"><i class='icon-link'></i>
898
</a><a href="#L899" id="L899" rel="#L899"><i class='icon-link'></i>
899
</a><a href="#L900" id="L900" rel="#L900"><i class='icon-link'></i>
900
</a><a href="#L901" id="L901" rel="#L901"><i class='icon-link'></i>
901
</a><a href="#L902" id="L902" rel="#L902"><i class='icon-link'></i>
902
</a><a href="#L903" id="L903" rel="#L903"><i class='icon-link'></i>
903
</a><a href="#L904" id="L904" rel="#L904"><i class='icon-link'></i>
904
</a><a href="#L905" id="L905" rel="#L905"><i class='icon-link'></i>
905
</a><a href="#L906" id="L906" rel="#L906"><i class='icon-link'></i>
906
</a><a href="#L907" id="L907" rel="#L907"><i class='icon-link'></i>
907
</a><a href="#L908" id="L908" rel="#L908"><i class='icon-link'></i>
908
</a><a href="#L909" id="L909" rel="#L909"><i class='icon-link'></i>
909
</a><a href="#L910" id="L910" rel="#L910"><i class='icon-link'></i>
910
</a><a href="#L911" id="L911" rel="#L911"><i class='icon-link'></i>
911
</a><a href="#L912" id="L912" rel="#L912"><i class='icon-link'></i>
912
</a><a href="#L913" id="L913" rel="#L913"><i class='icon-link'></i>
913
</a><a href="#L914" id="L914" rel="#L914"><i class='icon-link'></i>
914
</a><a href="#L915" id="L915" rel="#L915"><i class='icon-link'></i>
915
</a><a href="#L916" id="L916" rel="#L916"><i class='icon-link'></i>
916
</a><a href="#L917" id="L917" rel="#L917"><i class='icon-link'></i>
917
</a><a href="#L918" id="L918" rel="#L918"><i class='icon-link'></i>
918
</a><a href="#L919" id="L919" rel="#L919"><i class='icon-link'></i>
919
</a><a href="#L920" id="L920" rel="#L920"><i class='icon-link'></i>
920
</a><a href="#L921" id="L921" rel="#L921"><i class='icon-link'></i>
921
</a><a href="#L922" id="L922" rel="#L922"><i class='icon-link'></i>
922
</a><a href="#L923" id="L923" rel="#L923"><i class='icon-link'></i>
923
</a><a href="#L924" id="L924" rel="#L924"><i class='icon-link'></i>
924
</a><a href="#L925" id="L925" rel="#L925"><i class='icon-link'></i>
925
</a><a href="#L926" id="L926" rel="#L926"><i class='icon-link'></i>
926
</a><a href="#L927" id="L927" rel="#L927"><i class='icon-link'></i>
927
</a><a href="#L928" id="L928" rel="#L928"><i class='icon-link'></i>
928
</a><a href="#L929" id="L929" rel="#L929"><i class='icon-link'></i>
929
</a><a href="#L930" id="L930" rel="#L930"><i class='icon-link'></i>
930
</a><a href="#L931" id="L931" rel="#L931"><i class='icon-link'></i>
931
</a><a href="#L932" id="L932" rel="#L932"><i class='icon-link'></i>
932
</a><a href="#L933" id="L933" rel="#L933"><i class='icon-link'></i>
933
</a><a href="#L934" id="L934" rel="#L934"><i class='icon-link'></i>
934
</a><a href="#L935" id="L935" rel="#L935"><i class='icon-link'></i>
935
</a><a href="#L936" id="L936" rel="#L936"><i class='icon-link'></i>
936
</a><a href="#L937" id="L937" rel="#L937"><i class='icon-link'></i>
937
</a><a href="#L938" id="L938" rel="#L938"><i class='icon-link'></i>
938
</a><a href="#L939" id="L939" rel="#L939"><i class='icon-link'></i>
939
</a><a href="#L940" id="L940" rel="#L940"><i class='icon-link'></i>
940
</a><a href="#L941" id="L941" rel="#L941"><i class='icon-link'></i>
941
</a><a href="#L942" id="L942" rel="#L942"><i class='icon-link'></i>
942
</a><a href="#L943" id="L943" rel="#L943"><i class='icon-link'></i>
943
</a><a href="#L944" id="L944" rel="#L944"><i class='icon-link'></i>
944
</a><a href="#L945" id="L945" rel="#L945"><i class='icon-link'></i>
945
</a><a href="#L946" id="L946" rel="#L946"><i class='icon-link'></i>
946
</a><a href="#L947" id="L947" rel="#L947"><i class='icon-link'></i>
947
</a><a href="#L948" id="L948" rel="#L948"><i class='icon-link'></i>
948
</a><a href="#L949" id="L949" rel="#L949"><i class='icon-link'></i>
949
</a><a href="#L950" id="L950" rel="#L950"><i class='icon-link'></i>
950
</a><a href="#L951" id="L951" rel="#L951"><i class='icon-link'></i>
951
</a><a href="#L952" id="L952" rel="#L952"><i class='icon-link'></i>
952
</a><a href="#L953" id="L953" rel="#L953"><i class='icon-link'></i>
953
</a><a href="#L954" id="L954" rel="#L954"><i class='icon-link'></i>
954
</a><a href="#L955" id="L955" rel="#L955"><i class='icon-link'></i>
955
</a><a href="#L956" id="L956" rel="#L956"><i class='icon-link'></i>
956
</a><a href="#L957" id="L957" rel="#L957"><i class='icon-link'></i>
957
</a><a href="#L958" id="L958" rel="#L958"><i class='icon-link'></i>
958
</a><a href="#L959" id="L959" rel="#L959"><i class='icon-link'></i>
959
</a><a href="#L960" id="L960" rel="#L960"><i class='icon-link'></i>
960
</a><a href="#L961" id="L961" rel="#L961"><i class='icon-link'></i>
961
</a><a href="#L962" id="L962" rel="#L962"><i class='icon-link'></i>
962
</a><a href="#L963" id="L963" rel="#L963"><i class='icon-link'></i>
963
</a><a href="#L964" id="L964" rel="#L964"><i class='icon-link'></i>
964
</a><a href="#L965" id="L965" rel="#L965"><i class='icon-link'></i>
965
</a><a href="#L966" id="L966" rel="#L966"><i class='icon-link'></i>
966
</a><a href="#L967" id="L967" rel="#L967"><i class='icon-link'></i>
967
</a><a href="#L968" id="L968" rel="#L968"><i class='icon-link'></i>
968
</a><a href="#L969" id="L969" rel="#L969"><i class='icon-link'></i>
969
</a><a href="#L970" id="L970" rel="#L970"><i class='icon-link'></i>
970
</a><a href="#L971" id="L971" rel="#L971"><i class='icon-link'></i>
971
</a><a href="#L972" id="L972" rel="#L972"><i class='icon-link'></i>
972
</a><a href="#L973" id="L973" rel="#L973"><i class='icon-link'></i>
973
</a><a href="#L974" id="L974" rel="#L974"><i class='icon-link'></i>
974
</a><a href="#L975" id="L975" rel="#L975"><i class='icon-link'></i>
975
</a><a href="#L976" id="L976" rel="#L976"><i class='icon-link'></i>
976
</a><a href="#L977" id="L977" rel="#L977"><i class='icon-link'></i>
977
</a><a href="#L978" id="L978" rel="#L978"><i class='icon-link'></i>
978
</a><a href="#L979" id="L979" rel="#L979"><i class='icon-link'></i>
979
</a><a href="#L980" id="L980" rel="#L980"><i class='icon-link'></i>
980
</a><a href="#L981" id="L981" rel="#L981"><i class='icon-link'></i>
981
</a><a href="#L982" id="L982" rel="#L982"><i class='icon-link'></i>
982
</a><a href="#L983" id="L983" rel="#L983"><i class='icon-link'></i>
983
</a><a href="#L984" id="L984" rel="#L984"><i class='icon-link'></i>
984
</a><a href="#L985" id="L985" rel="#L985"><i class='icon-link'></i>
985
</a><a href="#L986" id="L986" rel="#L986"><i class='icon-link'></i>
986
</a><a href="#L987" id="L987" rel="#L987"><i class='icon-link'></i>
987
</a><a href="#L988" id="L988" rel="#L988"><i class='icon-link'></i>
988
</a><a href="#L989" id="L989" rel="#L989"><i class='icon-link'></i>
989
</a><a href="#L990" id="L990" rel="#L990"><i class='icon-link'></i>
990
</a><a href="#L991" id="L991" rel="#L991"><i class='icon-link'></i>
991
</a><a href="#L992" id="L992" rel="#L992"><i class='icon-link'></i>
992
</a><a href="#L993" id="L993" rel="#L993"><i class='icon-link'></i>
993
</a><a href="#L994" id="L994" rel="#L994"><i class='icon-link'></i>
994
</a><a href="#L995" id="L995" rel="#L995"><i class='icon-link'></i>
995
</a><a href="#L996" id="L996" rel="#L996"><i class='icon-link'></i>
996
</a><a href="#L997" id="L997" rel="#L997"><i class='icon-link'></i>
997
</a><a href="#L998" id="L998" rel="#L998"><i class='icon-link'></i>
998
</a><a href="#L999" id="L999" rel="#L999"><i class='icon-link'></i>
999
</a><a href="#L1000" id="L1000" rel="#L1000"><i class='icon-link'></i>
1000
</a><a href="#L1001" id="L1001" rel="#L1001"><i class='icon-link'></i>
1001
</a><a href="#L1002" id="L1002" rel="#L1002"><i class='icon-link'></i>
1002
</a><a href="#L1003" id="L1003" rel="#L1003"><i class='icon-link'></i>
1003
</a><a href="#L1004" id="L1004" rel="#L1004"><i class='icon-link'></i>
1004
</a><a href="#L1005" id="L1005" rel="#L1005"><i class='icon-link'></i>
1005
</a><a href="#L1006" id="L1006" rel="#L1006"><i class='icon-link'></i>
1006
</a><a href="#L1007" id="L1007" rel="#L1007"><i class='icon-link'></i>
1007
</a><a href="#L1008" id="L1008" rel="#L1008"><i class='icon-link'></i>
1008
</a><a href="#L1009" id="L1009" rel="#L1009"><i class='icon-link'></i>
1009
</a><a href="#L1010" id="L1010" rel="#L1010"><i class='icon-link'></i>
1010
</a><a href="#L1011" id="L1011" rel="#L1011"><i class='icon-link'></i>
1011
</a><a href="#L1012" id="L1012" rel="#L1012"><i class='icon-link'></i>
1012
</a><a href="#L1013" id="L1013" rel="#L1013"><i class='icon-link'></i>
1013
</a><a href="#L1014" id="L1014" rel="#L1014"><i class='icon-link'></i>
1014
</a><a href="#L1015" id="L1015" rel="#L1015"><i class='icon-link'></i>
1015
</a><a href="#L1016" id="L1016" rel="#L1016"><i class='icon-link'></i>
1016
</a><a href="#L1017" id="L1017" rel="#L1017"><i class='icon-link'></i>
1017
</a><a href="#L1018" id="L1018" rel="#L1018"><i class='icon-link'></i>
1018
</a><a href="#L1019" id="L1019" rel="#L1019"><i class='icon-link'></i>
1019
</a><a href="#L1020" id="L1020" rel="#L1020"><i class='icon-link'></i>
1020
</a><a href="#L1021" id="L1021" rel="#L1021"><i class='icon-link'></i>
1021
</a><a href="#L1022" id="L1022" rel="#L1022"><i class='icon-link'></i>
1022
</a><a href="#L1023" id="L1023" rel="#L1023"><i class='icon-link'></i>
1023
</a><a href="#L1024" id="L1024" rel="#L1024"><i class='icon-link'></i>
1024
</a><a href="#L1025" id="L1025" rel="#L1025"><i class='icon-link'></i>
1025
</a><a href="#L1026" id="L1026" rel="#L1026"><i class='icon-link'></i>
1026
</a><a href="#L1027" id="L1027" rel="#L1027"><i class='icon-link'></i>
1027
</a><a href="#L1028" id="L1028" rel="#L1028"><i class='icon-link'></i>
1028
</a><a href="#L1029" id="L1029" rel="#L1029"><i class='icon-link'></i>
1029
</a><a href="#L1030" id="L1030" rel="#L1030"><i class='icon-link'></i>
1030
</a><a href="#L1031" id="L1031" rel="#L1031"><i class='icon-link'></i>
1031
</a><a href="#L1032" id="L1032" rel="#L1032"><i class='icon-link'></i>
1032
</a><a href="#L1033" id="L1033" rel="#L1033"><i class='icon-link'></i>
1033
</a><a href="#L1034" id="L1034" rel="#L1034"><i class='icon-link'></i>
1034
</a><a href="#L1035" id="L1035" rel="#L1035"><i class='icon-link'></i>
1035
</a><a href="#L1036" id="L1036" rel="#L1036"><i class='icon-link'></i>
1036
</a><a href="#L1037" id="L1037" rel="#L1037"><i class='icon-link'></i>
1037
</a><a href="#L1038" id="L1038" rel="#L1038"><i class='icon-link'></i>
1038
</a><a href="#L1039" id="L1039" rel="#L1039"><i class='icon-link'></i>
1039
</a><a href="#L1040" id="L1040" rel="#L1040"><i class='icon-link'></i>
1040
</a><a href="#L1041" id="L1041" rel="#L1041"><i class='icon-link'></i>
1041
</a><a href="#L1042" id="L1042" rel="#L1042"><i class='icon-link'></i>
1042
</a><a href="#L1043" id="L1043" rel="#L1043"><i class='icon-link'></i>
1043
</a><a href="#L1044" id="L1044" rel="#L1044"><i class='icon-link'></i>
1044
</a><a href="#L1045" id="L1045" rel="#L1045"><i class='icon-link'></i>
1045
</a><a href="#L1046" id="L1046" rel="#L1046"><i class='icon-link'></i>
1046
</a><a href="#L1047" id="L1047" rel="#L1047"><i class='icon-link'></i>
1047
</a><a href="#L1048" id="L1048" rel="#L1048"><i class='icon-link'></i>
1048
</a><a href="#L1049" id="L1049" rel="#L1049"><i class='icon-link'></i>
1049
</a><a href="#L1050" id="L1050" rel="#L1050"><i class='icon-link'></i>
1050
</a><a href="#L1051" id="L1051" rel="#L1051"><i class='icon-link'></i>
1051
</a><a href="#L1052" id="L1052" rel="#L1052"><i class='icon-link'></i>
1052
</a><a href="#L1053" id="L1053" rel="#L1053"><i class='icon-link'></i>
1053
</a><a href="#L1054" id="L1054" rel="#L1054"><i class='icon-link'></i>
1054
</a><a href="#L1055" id="L1055" rel="#L1055"><i class='icon-link'></i>
1055
</a><a href="#L1056" id="L1056" rel="#L1056"><i class='icon-link'></i>
1056
</a><a href="#L1057" id="L1057" rel="#L1057"><i class='icon-link'></i>
1057
</a><a href="#L1058" id="L1058" rel="#L1058"><i class='icon-link'></i>
1058
</a><a href="#L1059" id="L1059" rel="#L1059"><i class='icon-link'></i>
1059
</a><a href="#L1060" id="L1060" rel="#L1060"><i class='icon-link'></i>
1060
</a><a href="#L1061" id="L1061" rel="#L1061"><i class='icon-link'></i>
1061
</a><a href="#L1062" id="L1062" rel="#L1062"><i class='icon-link'></i>
1062
</a><a href="#L1063" id="L1063" rel="#L1063"><i class='icon-link'></i>
1063
</a><a href="#L1064" id="L1064" rel="#L1064"><i class='icon-link'></i>
1064
</a><a href="#L1065" id="L1065" rel="#L1065"><i class='icon-link'></i>
1065
</a><a href="#L1066" id="L1066" rel="#L1066"><i class='icon-link'></i>
1066
</a><a href="#L1067" id="L1067" rel="#L1067"><i class='icon-link'></i>
1067
</a><a href="#L1068" id="L1068" rel="#L1068"><i class='icon-link'></i>
1068
</a><a href="#L1069" id="L1069" rel="#L1069"><i class='icon-link'></i>
1069
</a><a href="#L1070" id="L1070" rel="#L1070"><i class='icon-link'></i>
1070
</a><a href="#L1071" id="L1071" rel="#L1071"><i class='icon-link'></i>
1071
</a><a href="#L1072" id="L1072" rel="#L1072"><i class='icon-link'></i>
1072
</a><a href="#L1073" id="L1073" rel="#L1073"><i class='icon-link'></i>
1073
</a><a href="#L1074" id="L1074" rel="#L1074"><i class='icon-link'></i>
1074
</a><a href="#L1075" id="L1075" rel="#L1075"><i class='icon-link'></i>
1075
</a><a href="#L1076" id="L1076" rel="#L1076"><i class='icon-link'></i>
1076
</a><a href="#L1077" id="L1077" rel="#L1077"><i class='icon-link'></i>
1077
</a><a href="#L1078" id="L1078" rel="#L1078"><i class='icon-link'></i>
1078
</a><a href="#L1079" id="L1079" rel="#L1079"><i class='icon-link'></i>
1079
</a><a href="#L1080" id="L1080" rel="#L1080"><i class='icon-link'></i>
1080
</a><a href="#L1081" id="L1081" rel="#L1081"><i class='icon-link'></i>
1081
</a><a href="#L1082" id="L1082" rel="#L1082"><i class='icon-link'></i>
1082
</a><a href="#L1083" id="L1083" rel="#L1083"><i class='icon-link'></i>
1083
</a><a href="#L1084" id="L1084" rel="#L1084"><i class='icon-link'></i>
1084
</a><a href="#L1085" id="L1085" rel="#L1085"><i class='icon-link'></i>
1085
</a><a href="#L1086" id="L1086" rel="#L1086"><i class='icon-link'></i>
1086
</a><a href="#L1087" id="L1087" rel="#L1087"><i class='icon-link'></i>
1087
</a><a href="#L1088" id="L1088" rel="#L1088"><i class='icon-link'></i>
1088
</a><a href="#L1089" id="L1089" rel="#L1089"><i class='icon-link'></i>
1089
</a><a href="#L1090" id="L1090" rel="#L1090"><i class='icon-link'></i>
1090
</a><a href="#L1091" id="L1091" rel="#L1091"><i class='icon-link'></i>
1091
</a><a href="#L1092" id="L1092" rel="#L1092"><i class='icon-link'></i>
1092
</a><a href="#L1093" id="L1093" rel="#L1093"><i class='icon-link'></i>
1093
</a><a href="#L1094" id="L1094" rel="#L1094"><i class='icon-link'></i>
1094
</a><a href="#L1095" id="L1095" rel="#L1095"><i class='icon-link'></i>
1095
</a><a href="#L1096" id="L1096" rel="#L1096"><i class='icon-link'></i>
1096
</a><a href="#L1097" id="L1097" rel="#L1097"><i class='icon-link'></i>
1097
</a><a href="#L1098" id="L1098" rel="#L1098"><i class='icon-link'></i>
1098
</a><a href="#L1099" id="L1099" rel="#L1099"><i class='icon-link'></i>
1099
</a><a href="#L1100" id="L1100" rel="#L1100"><i class='icon-link'></i>
1100
</a><a href="#L1101" id="L1101" rel="#L1101"><i class='icon-link'></i>
1101
</a><a href="#L1102" id="L1102" rel="#L1102"><i class='icon-link'></i>
1102
</a><a href="#L1103" id="L1103" rel="#L1103"><i class='icon-link'></i>
1103
</a><a href="#L1104" id="L1104" rel="#L1104"><i class='icon-link'></i>
1104
</a><a href="#L1105" id="L1105" rel="#L1105"><i class='icon-link'></i>
1105
</a><a href="#L1106" id="L1106" rel="#L1106"><i class='icon-link'></i>
1106
</a><a href="#L1107" id="L1107" rel="#L1107"><i class='icon-link'></i>
1107
</a><a href="#L1108" id="L1108" rel="#L1108"><i class='icon-link'></i>
1108
</a><a href="#L1109" id="L1109" rel="#L1109"><i class='icon-link'></i>
1109
</a><a href="#L1110" id="L1110" rel="#L1110"><i class='icon-link'></i>
1110
</a><a href="#L1111" id="L1111" rel="#L1111"><i class='icon-link'></i>
1111
</a><a href="#L1112" id="L1112" rel="#L1112"><i class='icon-link'></i>
1112
</a><a href="#L1113" id="L1113" rel="#L1113"><i class='icon-link'></i>
1113
</a><a href="#L1114" id="L1114" rel="#L1114"><i class='icon-link'></i>
1114
</a><a href="#L1115" id="L1115" rel="#L1115"><i class='icon-link'></i>
1115
</a><a href="#L1116" id="L1116" rel="#L1116"><i class='icon-link'></i>
1116
</a><a href="#L1117" id="L1117" rel="#L1117"><i class='icon-link'></i>
1117
</a><a href="#L1118" id="L1118" rel="#L1118"><i class='icon-link'></i>
1118
</a><a href="#L1119" id="L1119" rel="#L1119"><i class='icon-link'></i>
1119
</a><a href="#L1120" id="L1120" rel="#L1120"><i class='icon-link'></i>
1120
</a><a href="#L1121" id="L1121" rel="#L1121"><i class='icon-link'></i>
1121
</a><a href="#L1122" id="L1122" rel="#L1122"><i class='icon-link'></i>
1122
</a><a href="#L1123" id="L1123" rel="#L1123"><i class='icon-link'></i>
1123
</a><a href="#L1124" id="L1124" rel="#L1124"><i class='icon-link'></i>
1124
</a><a href="#L1125" id="L1125" rel="#L1125"><i class='icon-link'></i>
1125
</a><a href="#L1126" id="L1126" rel="#L1126"><i class='icon-link'></i>
1126
</a><a href="#L1127" id="L1127" rel="#L1127"><i class='icon-link'></i>
1127
</a><a href="#L1128" id="L1128" rel="#L1128"><i class='icon-link'></i>
1128
</a><a href="#L1129" id="L1129" rel="#L1129"><i class='icon-link'></i>
1129
</a><a href="#L1130" id="L1130" rel="#L1130"><i class='icon-link'></i>
1130
</a><a href="#L1131" id="L1131" rel="#L1131"><i class='icon-link'></i>
1131
</a><a href="#L1132" id="L1132" rel="#L1132"><i class='icon-link'></i>
1132
</a><a href="#L1133" id="L1133" rel="#L1133"><i class='icon-link'></i>
1133
</a><a href="#L1134" id="L1134" rel="#L1134"><i class='icon-link'></i>
1134
</a><a href="#L1135" id="L1135" rel="#L1135"><i class='icon-link'></i>
1135
</a><a href="#L1136" id="L1136" rel="#L1136"><i class='icon-link'></i>
1136
</a><a href="#L1137" id="L1137" rel="#L1137"><i class='icon-link'></i>
1137
</a><a href="#L1138" id="L1138" rel="#L1138"><i class='icon-link'></i>
1138
</a><a href="#L1139" id="L1139" rel="#L1139"><i class='icon-link'></i>
1139
</a><a href="#L1140" id="L1140" rel="#L1140"><i class='icon-link'></i>
1140
</a><a href="#L1141" id="L1141" rel="#L1141"><i class='icon-link'></i>
1141
</a><a href="#L1142" id="L1142" rel="#L1142"><i class='icon-link'></i>
1142
</a><a href="#L1143" id="L1143" rel="#L1143"><i class='icon-link'></i>
1143
</a><a href="#L1144" id="L1144" rel="#L1144"><i class='icon-link'></i>
1144
</a><a href="#L1145" id="L1145" rel="#L1145"><i class='icon-link'></i>
1145
</a><a href="#L1146" id="L1146" rel="#L1146"><i class='icon-link'></i>
1146
</a><a href="#L1147" id="L1147" rel="#L1147"><i class='icon-link'></i>
1147
</a><a href="#L1148" id="L1148" rel="#L1148"><i class='icon-link'></i>
1148
</a><a href="#L1149" id="L1149" rel="#L1149"><i class='icon-link'></i>
1149
</a><a href="#L1150" id="L1150" rel="#L1150"><i class='icon-link'></i>
1150
</a><a href="#L1151" id="L1151" rel="#L1151"><i class='icon-link'></i>
1151
</a><a href="#L1152" id="L1152" rel="#L1152"><i class='icon-link'></i>
1152
</a><a href="#L1153" id="L1153" rel="#L1153"><i class='icon-link'></i>
1153
</a><a href="#L1154" id="L1154" rel="#L1154"><i class='icon-link'></i>
1154
</a><a href="#L1155" id="L1155" rel="#L1155"><i class='icon-link'></i>
1155
</a><a href="#L1156" id="L1156" rel="#L1156"><i class='icon-link'></i>
1156
</a><a href="#L1157" id="L1157" rel="#L1157"><i class='icon-link'></i>
1157
</a><a href="#L1158" id="L1158" rel="#L1158"><i class='icon-link'></i>
1158
</a><a href="#L1159" id="L1159" rel="#L1159"><i class='icon-link'></i>
1159
</a><a href="#L1160" id="L1160" rel="#L1160"><i class='icon-link'></i>
1160
</a><a href="#L1161" id="L1161" rel="#L1161"><i class='icon-link'></i>
1161
</a><a href="#L1162" id="L1162" rel="#L1162"><i class='icon-link'></i>
1162
</a><a href="#L1163" id="L1163" rel="#L1163"><i class='icon-link'></i>
1163
</a><a href="#L1164" id="L1164" rel="#L1164"><i class='icon-link'></i>
1164
</a><a href="#L1165" id="L1165" rel="#L1165"><i class='icon-link'></i>
1165
</a><a href="#L1166" id="L1166" rel="#L1166"><i class='icon-link'></i>
1166
</a><a href="#L1167" id="L1167" rel="#L1167"><i class='icon-link'></i>
1167
</a><a href="#L1168" id="L1168" rel="#L1168"><i class='icon-link'></i>
1168
</a><a href="#L1169" id="L1169" rel="#L1169"><i class='icon-link'></i>
1169
</a><a href="#L1170" id="L1170" rel="#L1170"><i class='icon-link'></i>
1170
</a><a href="#L1171" id="L1171" rel="#L1171"><i class='icon-link'></i>
1171
</a><a href="#L1172" id="L1172" rel="#L1172"><i class='icon-link'></i>
1172
</a><a href="#L1173" id="L1173" rel="#L1173"><i class='icon-link'></i>
1173
</a><a href="#L1174" id="L1174" rel="#L1174"><i class='icon-link'></i>
1174
</a><a href="#L1175" id="L1175" rel="#L1175"><i class='icon-link'></i>
1175
</a><a href="#L1176" id="L1176" rel="#L1176"><i class='icon-link'></i>
1176
</a><a href="#L1177" id="L1177" rel="#L1177"><i class='icon-link'></i>
1177
</a><a href="#L1178" id="L1178" rel="#L1178"><i class='icon-link'></i>
1178
</a><a href="#L1179" id="L1179" rel="#L1179"><i class='icon-link'></i>
1179
</a><a href="#L1180" id="L1180" rel="#L1180"><i class='icon-link'></i>
1180
</a><a href="#L1181" id="L1181" rel="#L1181"><i class='icon-link'></i>
1181
</a><a href="#L1182" id="L1182" rel="#L1182"><i class='icon-link'></i>
1182
</a><a href="#L1183" id="L1183" rel="#L1183"><i class='icon-link'></i>
1183
</a><a href="#L1184" id="L1184" rel="#L1184"><i class='icon-link'></i>
1184
</a><a href="#L1185" id="L1185" rel="#L1185"><i class='icon-link'></i>
1185
</a><a href="#L1186" id="L1186" rel="#L1186"><i class='icon-link'></i>
1186
</a><a href="#L1187" id="L1187" rel="#L1187"><i class='icon-link'></i>
1187
</a><a href="#L1188" id="L1188" rel="#L1188"><i class='icon-link'></i>
1188
</a><a href="#L1189" id="L1189" rel="#L1189"><i class='icon-link'></i>
1189
</a><a href="#L1190" id="L1190" rel="#L1190"><i class='icon-link'></i>
1190
</a><a href="#L1191" id="L1191" rel="#L1191"><i class='icon-link'></i>
1191
</a><a href="#L1192" id="L1192" rel="#L1192"><i class='icon-link'></i>
1192
</a><a href="#L1193" id="L1193" rel="#L1193"><i class='icon-link'></i>
1193
</a><a href="#L1194" id="L1194" rel="#L1194"><i class='icon-link'></i>
1194
</a><a href="#L1195" id="L1195" rel="#L1195"><i class='icon-link'></i>
1195
</a><a href="#L1196" id="L1196" rel="#L1196"><i class='icon-link'></i>
1196
</a><a href="#L1197" id="L1197" rel="#L1197"><i class='icon-link'></i>
1197
</a><a href="#L1198" id="L1198" rel="#L1198"><i class='icon-link'></i>
1198
</a><a href="#L1199" id="L1199" rel="#L1199"><i class='icon-link'></i>
1199
</a><a href="#L1200" id="L1200" rel="#L1200"><i class='icon-link'></i>
1200
</a><a href="#L1201" id="L1201" rel="#L1201"><i class='icon-link'></i>
1201
</a><a href="#L1202" id="L1202" rel="#L1202"><i class='icon-link'></i>
1202
</a><a href="#L1203" id="L1203" rel="#L1203"><i class='icon-link'></i>
1203
</a><a href="#L1204" id="L1204" rel="#L1204"><i class='icon-link'></i>
1204
</a><a href="#L1205" id="L1205" rel="#L1205"><i class='icon-link'></i>
1205
</a><a href="#L1206" id="L1206" rel="#L1206"><i class='icon-link'></i>
1206
</a><a href="#L1207" id="L1207" rel="#L1207"><i class='icon-link'></i>
1207
</a><a href="#L1208" id="L1208" rel="#L1208"><i class='icon-link'></i>
1208
</a><a href="#L1209" id="L1209" rel="#L1209"><i class='icon-link'></i>
1209
</a><a href="#L1210" id="L1210" rel="#L1210"><i class='icon-link'></i>
1210
</a><a href="#L1211" id="L1211" rel="#L1211"><i class='icon-link'></i>
1211
</a><a href="#L1212" id="L1212" rel="#L1212"><i class='icon-link'></i>
1212
</a><a href="#L1213" id="L1213" rel="#L1213"><i class='icon-link'></i>
1213
</a><a href="#L1214" id="L1214" rel="#L1214"><i class='icon-link'></i>
1214
</a><a href="#L1215" id="L1215" rel="#L1215"><i class='icon-link'></i>
1215
</a><a href="#L1216" id="L1216" rel="#L1216"><i class='icon-link'></i>
1216
</a><a href="#L1217" id="L1217" rel="#L1217"><i class='icon-link'></i>
1217
</a><a href="#L1218" id="L1218" rel="#L1218"><i class='icon-link'></i>
1218
</a><a href="#L1219" id="L1219" rel="#L1219"><i class='icon-link'></i>
1219
</a><a href="#L1220" id="L1220" rel="#L1220"><i class='icon-link'></i>
1220
</a><a href="#L1221" id="L1221" rel="#L1221"><i class='icon-link'></i>
1221
</a><a href="#L1222" id="L1222" rel="#L1222"><i class='icon-link'></i>
1222
</a><a href="#L1223" id="L1223" rel="#L1223"><i class='icon-link'></i>
1223
</a><a href="#L1224" id="L1224" rel="#L1224"><i class='icon-link'></i>
1224
</a><a href="#L1225" id="L1225" rel="#L1225"><i class='icon-link'></i>
1225
</a><a href="#L1226" id="L1226" rel="#L1226"><i class='icon-link'></i>
1226
</a><a href="#L1227" id="L1227" rel="#L1227"><i class='icon-link'></i>
1227
</a><a href="#L1228" id="L1228" rel="#L1228"><i class='icon-link'></i>
1228
</a><a href="#L1229" id="L1229" rel="#L1229"><i class='icon-link'></i>
1229
</a><a href="#L1230" id="L1230" rel="#L1230"><i class='icon-link'></i>
1230
</a><a href="#L1231" id="L1231" rel="#L1231"><i class='icon-link'></i>
1231
</a><a href="#L1232" id="L1232" rel="#L1232"><i class='icon-link'></i>
1232
</a><a href="#L1233" id="L1233" rel="#L1233"><i class='icon-link'></i>
1233
</a><a href="#L1234" id="L1234" rel="#L1234"><i class='icon-link'></i>
1234
</a><a href="#L1235" id="L1235" rel="#L1235"><i class='icon-link'></i>
1235
</a><a href="#L1236" id="L1236" rel="#L1236"><i class='icon-link'></i>
1236
</a><a href="#L1237" id="L1237" rel="#L1237"><i class='icon-link'></i>
1237
</a><a href="#L1238" id="L1238" rel="#L1238"><i class='icon-link'></i>
1238
</a><a href="#L1239" id="L1239" rel="#L1239"><i class='icon-link'></i>
1239
</a><a href="#L1240" id="L1240" rel="#L1240"><i class='icon-link'></i>
1240
</a><a href="#L1241" id="L1241" rel="#L1241"><i class='icon-link'></i>
1241
</a><a href="#L1242" id="L1242" rel="#L1242"><i class='icon-link'></i>
1242
</a><a href="#L1243" id="L1243" rel="#L1243"><i class='icon-link'></i>
1243
</a><a href="#L1244" id="L1244" rel="#L1244"><i class='icon-link'></i>
1244
</a><a href="#L1245" id="L1245" rel="#L1245"><i class='icon-link'></i>
1245
</a><a href="#L1246" id="L1246" rel="#L1246"><i class='icon-link'></i>
1246
</a><a href="#L1247" id="L1247" rel="#L1247"><i class='icon-link'></i>
1247
</a><a href="#L1248" id="L1248" rel="#L1248"><i class='icon-link'></i>
1248
</a><a href="#L1249" id="L1249" rel="#L1249"><i class='icon-link'></i>
1249
</a><a href="#L1250" id="L1250" rel="#L1250"><i class='icon-link'></i>
1250
</a><a href="#L1251" id="L1251" rel="#L1251"><i class='icon-link'></i>
1251
</a><a href="#L1252" id="L1252" rel="#L1252"><i class='icon-link'></i>
1252
</a><a href="#L1253" id="L1253" rel="#L1253"><i class='icon-link'></i>
1253
</a><a href="#L1254" id="L1254" rel="#L1254"><i class='icon-link'></i>
1254
</a><a href="#L1255" id="L1255" rel="#L1255"><i class='icon-link'></i>
1255
</a><a href="#L1256" id="L1256" rel="#L1256"><i class='icon-link'></i>
1256
</a><a href="#L1257" id="L1257" rel="#L1257"><i class='icon-link'></i>
1257
</a><a href="#L1258" id="L1258" rel="#L1258"><i class='icon-link'></i>
1258
</a><a href="#L1259" id="L1259" rel="#L1259"><i class='icon-link'></i>
1259
</a><a href="#L1260" id="L1260" rel="#L1260"><i class='icon-link'></i>
1260
</a><a href="#L1261" id="L1261" rel="#L1261"><i class='icon-link'></i>
1261
</a><a href="#L1262" id="L1262" rel="#L1262"><i class='icon-link'></i>
1262
</a><a href="#L1263" id="L1263" rel="#L1263"><i class='icon-link'></i>
1263
</a><a href="#L1264" id="L1264" rel="#L1264"><i class='icon-link'></i>
1264
</a><a href="#L1265" id="L1265" rel="#L1265"><i class='icon-link'></i>
1265
</a><a href="#L1266" id="L1266" rel="#L1266"><i class='icon-link'></i>
1266
</a><a href="#L1267" id="L1267" rel="#L1267"><i class='icon-link'></i>
1267
</a><a href="#L1268" id="L1268" rel="#L1268"><i class='icon-link'></i>
1268
</a><a href="#L1269" id="L1269" rel="#L1269"><i class='icon-link'></i>
1269
</a><a href="#L1270" id="L1270" rel="#L1270"><i class='icon-link'></i>
1270
</a><a href="#L1271" id="L1271" rel="#L1271"><i class='icon-link'></i>
1271
</a><a href="#L1272" id="L1272" rel="#L1272"><i class='icon-link'></i>
1272
</a><a href="#L1273" id="L1273" rel="#L1273"><i class='icon-link'></i>
1273
</a><a href="#L1274" id="L1274" rel="#L1274"><i class='icon-link'></i>
1274
</a><a href="#L1275" id="L1275" rel="#L1275"><i class='icon-link'></i>
1275
</a><a href="#L1276" id="L1276" rel="#L1276"><i class='icon-link'></i>
1276
</a><a href="#L1277" id="L1277" rel="#L1277"><i class='icon-link'></i>
1277
</a><a href="#L1278" id="L1278" rel="#L1278"><i class='icon-link'></i>
1278
</a><a href="#L1279" id="L1279" rel="#L1279"><i class='icon-link'></i>
1279
</a><a href="#L1280" id="L1280" rel="#L1280"><i class='icon-link'></i>
1280
</a><a href="#L1281" id="L1281" rel="#L1281"><i class='icon-link'></i>
1281
</a><a href="#L1282" id="L1282" rel="#L1282"><i class='icon-link'></i>
1282
</a><a href="#L1283" id="L1283" rel="#L1283"><i class='icon-link'></i>
1283
</a><a href="#L1284" id="L1284" rel="#L1284"><i class='icon-link'></i>
1284
</a><a href="#L1285" id="L1285" rel="#L1285"><i class='icon-link'></i>
1285
</a><a href="#L1286" id="L1286" rel="#L1286"><i class='icon-link'></i>
1286
</a><a href="#L1287" id="L1287" rel="#L1287"><i class='icon-link'></i>
1287
</a><a href="#L1288" id="L1288" rel="#L1288"><i class='icon-link'></i>
1288
</a><a href="#L1289" id="L1289" rel="#L1289"><i class='icon-link'></i>
1289
</a><a href="#L1290" id="L1290" rel="#L1290"><i class='icon-link'></i>
1290
</a><a href="#L1291" id="L1291" rel="#L1291"><i class='icon-link'></i>
1291
</a><a href="#L1292" id="L1292" rel="#L1292"><i class='icon-link'></i>
1292
</a><a href="#L1293" id="L1293" rel="#L1293"><i class='icon-link'></i>
1293
</a><a href="#L1294" id="L1294" rel="#L1294"><i class='icon-link'></i>
1294
</a><a href="#L1295" id="L1295" rel="#L1295"><i class='icon-link'></i>
1295
</a><a href="#L1296" id="L1296" rel="#L1296"><i class='icon-link'></i>
1296
</a><a href="#L1297" id="L1297" rel="#L1297"><i class='icon-link'></i>
1297
</a><a href="#L1298" id="L1298" rel="#L1298"><i class='icon-link'></i>
1298
</a><a href="#L1299" id="L1299" rel="#L1299"><i class='icon-link'></i>
1299
</a><a href="#L1300" id="L1300" rel="#L1300"><i class='icon-link'></i>
1300
</a><a href="#L1301" id="L1301" rel="#L1301"><i class='icon-link'></i>
1301
</a><a href="#L1302" id="L1302" rel="#L1302"><i class='icon-link'></i>
1302
</a><a href="#L1303" id="L1303" rel="#L1303"><i class='icon-link'></i>
1303
</a><a href="#L1304" id="L1304" rel="#L1304"><i class='icon-link'></i>
1304
</a><a href="#L1305" id="L1305" rel="#L1305"><i class='icon-link'></i>
1305
</a><a href="#L1306" id="L1306" rel="#L1306"><i class='icon-link'></i>
1306
</a><a href="#L1307" id="L1307" rel="#L1307"><i class='icon-link'></i>
1307
</a><a href="#L1308" id="L1308" rel="#L1308"><i class='icon-link'></i>
1308
</a><a href="#L1309" id="L1309" rel="#L1309"><i class='icon-link'></i>
1309
</a><a href="#L1310" id="L1310" rel="#L1310"><i class='icon-link'></i>
1310
</a><a href="#L1311" id="L1311" rel="#L1311"><i class='icon-link'></i>
1311
</a><a href="#L1312" id="L1312" rel="#L1312"><i class='icon-link'></i>
1312
</a><a href="#L1313" id="L1313" rel="#L1313"><i class='icon-link'></i>
1313
</a><a href="#L1314" id="L1314" rel="#L1314"><i class='icon-link'></i>
1314
</a><a href="#L1315" id="L1315" rel="#L1315"><i class='icon-link'></i>
1315
</a><a href="#L1316" id="L1316" rel="#L1316"><i class='icon-link'></i>
1316
</a><a href="#L1317" id="L1317" rel="#L1317"><i class='icon-link'></i>
1317
</a><a href="#L1318" id="L1318" rel="#L1318"><i class='icon-link'></i>
1318
</a><a href="#L1319" id="L1319" rel="#L1319"><i class='icon-link'></i>
1319
</a><a href="#L1320" id="L1320" rel="#L1320"><i class='icon-link'></i>
1320
</a><a href="#L1321" id="L1321" rel="#L1321"><i class='icon-link'></i>
1321
</a><a href="#L1322" id="L1322" rel="#L1322"><i class='icon-link'></i>
1322
</a><a href="#L1323" id="L1323" rel="#L1323"><i class='icon-link'></i>
1323
</a><a href="#L1324" id="L1324" rel="#L1324"><i class='icon-link'></i>
1324
</a><a href="#L1325" id="L1325" rel="#L1325"><i class='icon-link'></i>
1325
</a><a href="#L1326" id="L1326" rel="#L1326"><i class='icon-link'></i>
1326
</a><a href="#L1327" id="L1327" rel="#L1327"><i class='icon-link'></i>
1327
</a><a href="#L1328" id="L1328" rel="#L1328"><i class='icon-link'></i>
1328
</a><a href="#L1329" id="L1329" rel="#L1329"><i class='icon-link'></i>
1329
</a><a href="#L1330" id="L1330" rel="#L1330"><i class='icon-link'></i>
1330
</a><a href="#L1331" id="L1331" rel="#L1331"><i class='icon-link'></i>
1331
</a><a href="#L1332" id="L1332" rel="#L1332"><i class='icon-link'></i>
1332
</a><a href="#L1333" id="L1333" rel="#L1333"><i class='icon-link'></i>
1333
</a><a href="#L1334" id="L1334" rel="#L1334"><i class='icon-link'></i>
1334
</a><a href="#L1335" id="L1335" rel="#L1335"><i class='icon-link'></i>
1335
</a><a href="#L1336" id="L1336" rel="#L1336"><i class='icon-link'></i>
1336
</a><a href="#L1337" id="L1337" rel="#L1337"><i class='icon-link'></i>
1337
</a><a href="#L1338" id="L1338" rel="#L1338"><i class='icon-link'></i>
1338
</a><a href="#L1339" id="L1339" rel="#L1339"><i class='icon-link'></i>
1339
</a><a href="#L1340" id="L1340" rel="#L1340"><i class='icon-link'></i>
1340
</a><a href="#L1341" id="L1341" rel="#L1341"><i class='icon-link'></i>
1341
</a><a href="#L1342" id="L1342" rel="#L1342"><i class='icon-link'></i>
1342
</a><a href="#L1343" id="L1343" rel="#L1343"><i class='icon-link'></i>
1343
</a><a href="#L1344" id="L1344" rel="#L1344"><i class='icon-link'></i>
1344
</a><a href="#L1345" id="L1345" rel="#L1345"><i class='icon-link'></i>
1345
</a><a href="#L1346" id="L1346" rel="#L1346"><i class='icon-link'></i>
1346
</a><a href="#L1347" id="L1347" rel="#L1347"><i class='icon-link'></i>
1347
</a><a href="#L1348" id="L1348" rel="#L1348"><i class='icon-link'></i>
1348
</a><a href="#L1349" id="L1349" rel="#L1349"><i class='icon-link'></i>
1349
</a><a href="#L1350" id="L1350" rel="#L1350"><i class='icon-link'></i>
1350
</a><a href="#L1351" id="L1351" rel="#L1351"><i class='icon-link'></i>
1351
</a><a href="#L1352" id="L1352" rel="#L1352"><i class='icon-link'></i>
1352
</a><a href="#L1353" id="L1353" rel="#L1353"><i class='icon-link'></i>
1353
</a><a href="#L1354" id="L1354" rel="#L1354"><i class='icon-link'></i>
1354
</a><a href="#L1355" id="L1355" rel="#L1355"><i class='icon-link'></i>
1355
</a><a href="#L1356" id="L1356" rel="#L1356"><i class='icon-link'></i>
1356
</a><a href="#L1357" id="L1357" rel="#L1357"><i class='icon-link'></i>
1357
</a><a href="#L1358" id="L1358" rel="#L1358"><i class='icon-link'></i>
1358
</a><a href="#L1359" id="L1359" rel="#L1359"><i class='icon-link'></i>
1359
</a><a href="#L1360" id="L1360" rel="#L1360"><i class='icon-link'></i>
1360
</a><a href="#L1361" id="L1361" rel="#L1361"><i class='icon-link'></i>
1361
</a><a href="#L1362" id="L1362" rel="#L1362"><i class='icon-link'></i>
1362
</a><a href="#L1363" id="L1363" rel="#L1363"><i class='icon-link'></i>
1363
</a><a href="#L1364" id="L1364" rel="#L1364"><i class='icon-link'></i>
1364
</a><a href="#L1365" id="L1365" rel="#L1365"><i class='icon-link'></i>
1365
</a><a href="#L1366" id="L1366" rel="#L1366"><i class='icon-link'></i>
1366
</a><a href="#L1367" id="L1367" rel="#L1367"><i class='icon-link'></i>
1367
</a><a href="#L1368" id="L1368" rel="#L1368"><i class='icon-link'></i>
1368
</a><a href="#L1369" id="L1369" rel="#L1369"><i class='icon-link'></i>
1369
</a><a href="#L1370" id="L1370" rel="#L1370"><i class='icon-link'></i>
1370
</a><a href="#L1371" id="L1371" rel="#L1371"><i class='icon-link'></i>
1371
</a><a href="#L1372" id="L1372" rel="#L1372"><i class='icon-link'></i>
1372
</a><a href="#L1373" id="L1373" rel="#L1373"><i class='icon-link'></i>
1373
</a><a href="#L1374" id="L1374" rel="#L1374"><i class='icon-link'></i>
1374
</a><a href="#L1375" id="L1375" rel="#L1375"><i class='icon-link'></i>
1375
</a><a href="#L1376" id="L1376" rel="#L1376"><i class='icon-link'></i>
1376
</a><a href="#L1377" id="L1377" rel="#L1377"><i class='icon-link'></i>
1377
</a><a href="#L1378" id="L1378" rel="#L1378"><i class='icon-link'></i>
1378
</a><a href="#L1379" id="L1379" rel="#L1379"><i class='icon-link'></i>
1379
</a><a href="#L1380" id="L1380" rel="#L1380"><i class='icon-link'></i>
1380
</a><a href="#L1381" id="L1381" rel="#L1381"><i class='icon-link'></i>
1381
</a><a href="#L1382" id="L1382" rel="#L1382"><i class='icon-link'></i>
1382
</a><a href="#L1383" id="L1383" rel="#L1383"><i class='icon-link'></i>
1383
</a><a href="#L1384" id="L1384" rel="#L1384"><i class='icon-link'></i>
1384
</a><a href="#L1385" id="L1385" rel="#L1385"><i class='icon-link'></i>
1385
</a><a href="#L1386" id="L1386" rel="#L1386"><i class='icon-link'></i>
1386
</a><a href="#L1387" id="L1387" rel="#L1387"><i class='icon-link'></i>
1387
</a><a href="#L1388" id="L1388" rel="#L1388"><i class='icon-link'></i>
1388
</a><a href="#L1389" id="L1389" rel="#L1389"><i class='icon-link'></i>
1389
</a><a href="#L1390" id="L1390" rel="#L1390"><i class='icon-link'></i>
1390
</a><a href="#L1391" id="L1391" rel="#L1391"><i class='icon-link'></i>
1391
</a><a href="#L1392" id="L1392" rel="#L1392"><i class='icon-link'></i>
1392
</a><a href="#L1393" id="L1393" rel="#L1393"><i class='icon-link'></i>
1393
</a><a href="#L1394" id="L1394" rel="#L1394"><i class='icon-link'></i>
1394
</a><a href="#L1395" id="L1395" rel="#L1395"><i class='icon-link'></i>
1395
</a><a href="#L1396" id="L1396" rel="#L1396"><i class='icon-link'></i>
1396
</a><a href="#L1397" id="L1397" rel="#L1397"><i class='icon-link'></i>
1397
</a><a href="#L1398" id="L1398" rel="#L1398"><i class='icon-link'></i>
1398
</a><a href="#L1399" id="L1399" rel="#L1399"><i class='icon-link'></i>
1399
</a><a href="#L1400" id="L1400" rel="#L1400"><i class='icon-link'></i>
1400
</a><a href="#L1401" id="L1401" rel="#L1401"><i class='icon-link'></i>
1401
</a><a href="#L1402" id="L1402" rel="#L1402"><i class='icon-link'></i>
1402
</a><a href="#L1403" id="L1403" rel="#L1403"><i class='icon-link'></i>
1403
</a><a href="#L1404" id="L1404" rel="#L1404"><i class='icon-link'></i>
1404
</a><a href="#L1405" id="L1405" rel="#L1405"><i class='icon-link'></i>
1405
</a><a href="#L1406" id="L1406" rel="#L1406"><i class='icon-link'></i>
1406
</a><a href="#L1407" id="L1407" rel="#L1407"><i class='icon-link'></i>
1407
</a><a href="#L1408" id="L1408" rel="#L1408"><i class='icon-link'></i>
1408
</a><a href="#L1409" id="L1409" rel="#L1409"><i class='icon-link'></i>
1409
</a><a href="#L1410" id="L1410" rel="#L1410"><i class='icon-link'></i>
1410
</a><a href="#L1411" id="L1411" rel="#L1411"><i class='icon-link'></i>
1411
</a><a href="#L1412" id="L1412" rel="#L1412"><i class='icon-link'></i>
1412
</a><a href="#L1413" id="L1413" rel="#L1413"><i class='icon-link'></i>
1413
</a><a href="#L1414" id="L1414" rel="#L1414"><i class='icon-link'></i>
1414
</a><a href="#L1415" id="L1415" rel="#L1415"><i class='icon-link'></i>
1415
</a><a href="#L1416" id="L1416" rel="#L1416"><i class='icon-link'></i>
1416
</a><a href="#L1417" id="L1417" rel="#L1417"><i class='icon-link'></i>
1417
</a><a href="#L1418" id="L1418" rel="#L1418"><i class='icon-link'></i>
1418
</a><a href="#L1419" id="L1419" rel="#L1419"><i class='icon-link'></i>
1419
</a><a href="#L1420" id="L1420" rel="#L1420"><i class='icon-link'></i>
1420
</a><a href="#L1421" id="L1421" rel="#L1421"><i class='icon-link'></i>
1421
</a><a href="#L1422" id="L1422" rel="#L1422"><i class='icon-link'></i>
1422
</a><a href="#L1423" id="L1423" rel="#L1423"><i class='icon-link'></i>
1423
</a><a href="#L1424" id="L1424" rel="#L1424"><i class='icon-link'></i>
1424
</a><a href="#L1425" id="L1425" rel="#L1425"><i class='icon-link'></i>
1425
</a><a href="#L1426" id="L1426" rel="#L1426"><i class='icon-link'></i>
1426
</a><a href="#L1427" id="L1427" rel="#L1427"><i class='icon-link'></i>
1427
</a><a href="#L1428" id="L1428" rel="#L1428"><i class='icon-link'></i>
1428
</a><a href="#L1429" id="L1429" rel="#L1429"><i class='icon-link'></i>
1429
</a><a href="#L1430" id="L1430" rel="#L1430"><i class='icon-link'></i>
1430
</a><a href="#L1431" id="L1431" rel="#L1431"><i class='icon-link'></i>
1431
</a><a href="#L1432" id="L1432" rel="#L1432"><i class='icon-link'></i>
1432
</a><a href="#L1433" id="L1433" rel="#L1433"><i class='icon-link'></i>
1433
</a><a href="#L1434" id="L1434" rel="#L1434"><i class='icon-link'></i>
1434
</a><a href="#L1435" id="L1435" rel="#L1435"><i class='icon-link'></i>
1435
</a><a href="#L1436" id="L1436" rel="#L1436"><i class='icon-link'></i>
1436
</a><a href="#L1437" id="L1437" rel="#L1437"><i class='icon-link'></i>
1437
</a><a href="#L1438" id="L1438" rel="#L1438"><i class='icon-link'></i>
1438
</a><a href="#L1439" id="L1439" rel="#L1439"><i class='icon-link'></i>
1439
</a><a href="#L1440" id="L1440" rel="#L1440"><i class='icon-link'></i>
1440
</a><a href="#L1441" id="L1441" rel="#L1441"><i class='icon-link'></i>
1441
</a><a href="#L1442" id="L1442" rel="#L1442"><i class='icon-link'></i>
1442
</a><a href="#L1443" id="L1443" rel="#L1443"><i class='icon-link'></i>
1443
</a><a href="#L1444" id="L1444" rel="#L1444"><i class='icon-link'></i>
1444
</a><a href="#L1445" id="L1445" rel="#L1445"><i class='icon-link'></i>
1445
</a><a href="#L1446" id="L1446" rel="#L1446"><i class='icon-link'></i>
1446
</a><a href="#L1447" id="L1447" rel="#L1447"><i class='icon-link'></i>
1447
</a><a href="#L1448" id="L1448" rel="#L1448"><i class='icon-link'></i>
1448
</a><a href="#L1449" id="L1449" rel="#L1449"><i class='icon-link'></i>
1449
</a><a href="#L1450" id="L1450" rel="#L1450"><i class='icon-link'></i>
1450
</a><a href="#L1451" id="L1451" rel="#L1451"><i class='icon-link'></i>
1451
</a><a href="#L1452" id="L1452" rel="#L1452"><i class='icon-link'></i>
1452
</a><a href="#L1453" id="L1453" rel="#L1453"><i class='icon-link'></i>
1453
</a><a href="#L1454" id="L1454" rel="#L1454"><i class='icon-link'></i>
1454
</a><a href="#L1455" id="L1455" rel="#L1455"><i class='icon-link'></i>
1455
</a><a href="#L1456" id="L1456" rel="#L1456"><i class='icon-link'></i>
1456
</a><a href="#L1457" id="L1457" rel="#L1457"><i class='icon-link'></i>
1457
</a><a href="#L1458" id="L1458" rel="#L1458"><i class='icon-link'></i>
1458
</a><a href="#L1459" id="L1459" rel="#L1459"><i class='icon-link'></i>
1459
</a><a href="#L1460" id="L1460" rel="#L1460"><i class='icon-link'></i>
1460
</a><a href="#L1461" id="L1461" rel="#L1461"><i class='icon-link'></i>
1461
</a><a href="#L1462" id="L1462" rel="#L1462"><i class='icon-link'></i>
1462
</a><a href="#L1463" id="L1463" rel="#L1463"><i class='icon-link'></i>
1463
</a><a href="#L1464" id="L1464" rel="#L1464"><i class='icon-link'></i>
1464
</a><a href="#L1465" id="L1465" rel="#L1465"><i class='icon-link'></i>
1465
</a><a href="#L1466" id="L1466" rel="#L1466"><i class='icon-link'></i>
1466
</a><a href="#L1467" id="L1467" rel="#L1467"><i class='icon-link'></i>
1467
</a><a href="#L1468" id="L1468" rel="#L1468"><i class='icon-link'></i>
1468
</a><a href="#L1469" id="L1469" rel="#L1469"><i class='icon-link'></i>
1469
</a><a href="#L1470" id="L1470" rel="#L1470"><i class='icon-link'></i>
1470
</a><a href="#L1471" id="L1471" rel="#L1471"><i class='icon-link'></i>
1471
</a><a href="#L1472" id="L1472" rel="#L1472"><i class='icon-link'></i>
1472
</a><a href="#L1473" id="L1473" rel="#L1473"><i class='icon-link'></i>
1473
</a><a href="#L1474" id="L1474" rel="#L1474"><i class='icon-link'></i>
1474
</a><a href="#L1475" id="L1475" rel="#L1475"><i class='icon-link'></i>
1475
</a><a href="#L1476" id="L1476" rel="#L1476"><i class='icon-link'></i>
1476
</a><a href="#L1477" id="L1477" rel="#L1477"><i class='icon-link'></i>
1477
</a><a href="#L1478" id="L1478" rel="#L1478"><i class='icon-link'></i>
1478
</a><a href="#L1479" id="L1479" rel="#L1479"><i class='icon-link'></i>
1479
</a><a href="#L1480" id="L1480" rel="#L1480"><i class='icon-link'></i>
1480
</a><a href="#L1481" id="L1481" rel="#L1481"><i class='icon-link'></i>
1481
</a><a href="#L1482" id="L1482" rel="#L1482"><i class='icon-link'></i>
1482
</a><a href="#L1483" id="L1483" rel="#L1483"><i class='icon-link'></i>
1483
</a><a href="#L1484" id="L1484" rel="#L1484"><i class='icon-link'></i>
1484
</a><a href="#L1485" id="L1485" rel="#L1485"><i class='icon-link'></i>
1485
</a><a href="#L1486" id="L1486" rel="#L1486"><i class='icon-link'></i>
1486
</a><a href="#L1487" id="L1487" rel="#L1487"><i class='icon-link'></i>
1487
</a><a href="#L1488" id="L1488" rel="#L1488"><i class='icon-link'></i>
1488
</a></div>
<div class='highlight'>
<pre><code class='language-cs'>﻿namespace T3000.Forms
{
    using ExceptionHandling;
    using FastColoredTextBoxNS;
    using Irony;
    using Irony.Parsing;
    using PRGReaderLibrary.Extensions;
    using PRGReaderLibrary.Types.Enums.Codecs;
    using PRGReaderLibrary.Utilities;
    using System;
    using System.Collections.Generic;
    using System.Diagnostics;
    using System.Linq;
    using System.Text.RegularExpressions;
    using System.Windows.Forms;




    /// &lt;summary&gt;
    /// Delegate to event handler Send
    /// &lt;/summary&gt;
    /// &lt;param name=&quot;sender&quot;&gt;&lt;/param&gt;
    /// &lt;param name=&quot;e&quot;&gt;&lt;/param&gt;
    public delegate void SendEventHandler(object sender, SendEventArgs e);

    /// &lt;summary&gt;
    /// ProgramEditor Form
    /// &lt;/summary&gt;
    public partial class ProgramEditorForm : Form
    {

        /// &lt;summary&gt;
        /// Required copy of Control Points Labels just for semantic validations
        /// &lt;/summary&gt;
        public ControlPoints Identifiers { get; set; } = new ControlPoints();


        private string Code { get; set; }


        List&lt;EditorTokenInfo&gt; Tokens = new List&lt;EditorTokenInfo&gt;();

        //int ParsingTimes = 0;

        /// &lt;summary&gt;
        /// Form caption
        /// &lt;/summary&gt;
        public string Caption
        {
            get { return this.Text; }
            set { this.Text = value; }
        }



        Grammar _grammar;
        LanguageData _language;
        ParseTree _parseTree;
        Parser _parser;


        /// &lt;summary&gt;
        /// Stack of recursive examined functions, counting subexpressions
        /// &lt;/summary&gt;
        Stack&lt;EditorTokenInfo&gt; functions = new Stack&lt;EditorTokenInfo&gt;();
        /// &lt;summary&gt;
        /// Stack of recursive examined branches, counting subexpressions
        /// &lt;/summary&gt;
        Stack&lt;EditorTokenInfo&gt; branches = new Stack&lt;EditorTokenInfo&gt;();


        //Container of all line numbers
        List&lt;EditorLineInfo&gt; Lines;
        List&lt;EditorJumpInfo&gt; Jumps;
        long LastParseTime;

        /// &lt;summary&gt;
        /// Event Send
        /// &lt;/summary&gt;
        public event SendEventHandler Send;

        /// &lt;summary&gt;
        /// Overridable OnSend Event Handler
        /// &lt;/summary&gt;
        public void OnSend(SendEventArgs e)
        {

            Code = editTextBox.Text;

            //if (Send != null)
            //{
            //    Send(this, e);
            //}


            Send?.Invoke(this, e);


        }

        /// &lt;summary&gt;
        /// Default constructor of ProgramEditorForm
        /// Use: SetCode(string) to assign program code to Editor.
        /// &lt;/summary&gt;
        public ProgramEditorForm()
        {

            try
            {
                InitializeComponent();

                editTextBox.Font = new System.Drawing.Font(&quot;Courier New&quot;, 9.75F);
                editTextBox.Grammar = new T3000Grammar();
                editTextBox.SetParser(new LanguageData(editTextBox.Grammar));
                //LRUIZ :: Enable a new set of grammar, language and parser, to get Program Code Errors
                _grammar = new T3000Grammar();
                _language = new LanguageData(_grammar);
                _parser = new Parser(_language);
                //LRUIZ



                //var items = new List&lt;AutocompleteItem&gt;();
                var keywords = new List&lt;string&gt;()
            {
                &quot;REM&quot;,
                &quot;IF&quot;,
                &quot;IF-&quot;,
                &quot;IF+&quot;,
                &quot;THEN&quot;,
                &quot;ELSE&quot;,
                &quot;TIME-ON&quot;
            };
                keywords.AddRange(T3000Grammar.Functions);

                //foreach (var item in keywords)
                //    items.Add(new AutocompleteItem(item) { ImageIndex = 1 });

                //var snippets = new[]{
                //    &quot;if(^)\n{\n}&quot;,
                //    &quot;if(^)\n{\n}\nelse\n{\n}&quot;,
                //    &quot;for(^;;)\n{\n}&quot;, &quot;while(^)\n{\n}&quot;,
                //    &quot;do${\n^}while();&quot;,
                //    &quot;switch(^)\n{\n\tcase : break;\n}&quot;
                //};
                //foreach (var item in snippets)
                //    items.Add(new SnippetAutocompleteItem(item) { ImageIndex = 1 });

                //set as autocomplete source
                //autocompleteMenu.Items.SetAutocompleteItems(items);


                this.WindowState = FormWindowState.Maximized;
                //this.WindowState = FormWindowState.Normal;


            }
            catch (Exception ex)
            {
                ExceptionHandler.Show(ex, &quot;Initializing ProgramEditorForm, exception found&quot;);
            }

        }

        /// &lt;summary&gt;
        /// Get next line number
        /// &lt;/summary&gt;
        /// &lt;returns&gt;new line number (string)&lt;/returns&gt;
        string GetNextLineNumber()
        {

            Lines = new List&lt;EditorLineInfo&gt;();
            var lines = editTextBox.Text.ToLines(StringSplitOptions.RemoveEmptyEntries);
            //Preload ALL line numbers
            for (var i = 0; i &lt; lines.Count; i++)
            {
                var words = lines[i].Split(' ');

                var LINFO = new EditorLineInfo(Convert.ToInt32(words[0]), (i + 1) * 10);
                this.Lines.Add(LINFO);
            }

            return (Lines.LastOrDefault().Before + 10).ToString();

        }

        /// &lt;summary&gt;
        /// Try to renumber all lines and their references.
        /// Show errors as semantic ones.
        /// &lt;/summary&gt;
        public void LinesValidator()
        {

            if (_parseTree == null) return;

            if (_parseTree.ParserMessages.Any()) return;

            int pos = 0;
            int col = 0;
            bool Cancel = false;
            Lines = new List&lt;EditorLineInfo&gt;();
            Jumps = new List&lt;EditorJumpInfo&gt;();


            var lines = editTextBox.Text.ToLines(StringSplitOptions.RemoveEmptyEntries);

            //Preload ALL line numbers
            for (var i = 0; i &lt; lines.Count; i++)
            {
                var words = lines[i].Split(' ');

                var LINFO = new EditorLineInfo(Convert.ToInt32(words[0]), (i + 1) * 10);
                this.Lines.Add(LINFO);
            }

            for (var i = 0; i &lt; lines.Count; i++)
            {
                var words = lines[i].Split(' ');


                for (var j = 0; j &lt; words.Count(); j++)
                {
                    JumpType type = JumpType.GOTO;
                    int linenumber = -1;
                    int offset = 0;


                    switch (words[j])
                    {
                        case &quot;GOTO&quot;:
                        case &quot;GOSUB&quot;:
                        case &quot;ON-ERROR&quot;:
                        case &quot;ON-ALARM&quot;:
                        case &quot;THEN&quot;:

                            switch (words[j][0])
                            {
                                case 'G':
                                    type = words[j] == &quot;GOTO&quot; ? JumpType.GOTO : JumpType.GOSUB; break;
                                case 'O':
                                    type = words[j] == &quot;ON-ERROR&quot; ? JumpType.ONERROR : JumpType.ONALARM; break;
                                case 'T':
                                    type = JumpType.THEN; break;
                            }


                            offset = j + 1;
                            int BeforeLineNumber = -1;
                            if (!Int32.TryParse(words[offset], out BeforeLineNumber)) break;

                            //var BeforeLineNumber = Convert.ToInt32(words[offset]);
                            linenumber = Lines.FindIndex(k =&gt; k.Before == BeforeLineNumber);
                            if (linenumber == -1)
                            {
                                //There is a semantic error here
                                //Add error message to parser and cancel renumbering.
                                //Don't break it inmediately, to show all possible errors of this type
                                _parseTree.ParserMessages.Add(new LogMessage(ErrorLevel.Error,
                                    new SourceLocation(pos + words[j].Count() + 1, i, col + words[j].Count() + 1),
                                    $&quot;Semantic Error: Line number {BeforeLineNumber.ToString()} for {words[j]} does not exist&quot;,
                                    new ParserState(&quot;Validating Lines&quot;)));
                                ShowCompilerErrors();
                                Cancel = true;
                            }
                            EditorJumpInfo JINFO = new EditorJumpInfo(type, i, offset);
                            Jumps.Add(JINFO);
                            //Change reference to new linenumber
                            words[offset] = linenumber == -1 ? BeforeLineNumber.ToString() : Lines[linenumber].ToString();
                            break;

                    }//switch jumps
                    pos += words[j].Count() + 1;
                    col += words[j].Count() + 1;
                }//for words
                pos++;
                col = 0;
                //change current linenumber
                words[0] = Lines[i].ToString();
                lines[i] = string.Join(' '.ToString(), words);


            }//for lines
            string newcode = string.Join(Environment.NewLine, lines);
            if (Cancel) return;
            editTextBox.Text = newcode;
        }

        /// &lt;summary&gt;
        /// Set code to EditBox, ProgramCode is automatically parsed. 
        /// &lt;/summary&gt;
        /// &lt;param name=&quot;code&quot;&gt;String contaning plain text Control Basic with numbered lines {Not Bytes Encoded Programs}&lt;/param&gt;
        public void SetCode(string code)
        {
            Code = code;
            //editTextBox.Text = RemoveInitialNumbers(code);

            editTextBox.Text = Code;

            //LRUIZ: Parse and show syntax errors

            ParseCode(false);

        }

        private void cmdClear_Click(object sender, EventArgs e)
        {
            ClearCode();
        }

        /// &lt;summary&gt;
        /// Clear editBox only.
        /// If you want to update/clear the inner code, use SetCode
        /// &lt;/summary&gt;
        public void ClearCode()
        {
            //local member Code is not cleared, to allow recovering with REFRESH (F8)
            editTextBox.Text = &quot;&quot;;
        }

        /// &lt;summary&gt;
        /// Override of ToString -&gt; GetCode
        /// &lt;/summary&gt;
        /// &lt;returns&gt;&lt;/returns&gt;
        public override string ToString()
        {
            return GetCode();
        }

        /// &lt;summary&gt;
        /// Get current code
        /// &lt;/summary&gt;
        /// &lt;returns&gt;&lt;/returns&gt;
        public string GetCode()
        {
            Code = editTextBox.Text;
            return Code;
        }

        /// &lt;summary&gt;
        /// Forces parsing the code contained in EditTextBox
        /// &lt;/summary&gt;
        public void ParseCode(bool fullParsing = false)
        {
            ClearParserOutput();
            if (_parser == null || !_parser.Language.CanParse()) return;
            _parseTree = null;
            GC.Collect(); //to avoid disruption of perf times with occasional collections
            _parser.Context.TracingEnabled = true;
            try
            {
                Stopwatch stopwatch = Stopwatch.StartNew(); //creates and start the instance of Stopwatch

                _parser.Parse(editTextBox.Text, &quot;&lt;source&gt;&quot;);
                _parseTree = _parser.Context.CurrentParseTree;


                if (_parseTree.ParserMessages.Any() || _parseTree.HasErrors()) return;

                if (fullParsing) //Only do this checks in full parsing.
                {
                    LinesValidator(); // Check semantic errors on jumps and renumber lines.
                    ProcessTokens(); //Check for other semantic errors and make some changes to local list of tokens

                    if (_parseTree.ParserMessages.Any() || _parseTree.HasErrors())
                    {
                        MessageBox.Show($&quot;{_parseTree.ParserMessages.Count()} error(s) found!{Environment.NewLine}Compiler halted.&quot;, &quot;Semantic Errors Found!&quot;);
                        return;
                    }
                }


                System.Threading.Thread.Sleep(500);
                stopwatch.Stop();
                LastParseTime = stopwatch.ElapsedMilliseconds - 500;
                lblParseTime.Text = $&quot;Parse Time: {LastParseTime}ms&quot;;

            }
            catch (Exception ex)
            {
                gridCompileErrors.Rows.Add(null, ex.Message, null);

                //throw;
            }
            finally
            {

                ShowCompilerErrors();


                ShowCompileStats();

            }
        }

        private void ClearParserOutput()
        {

            lblSrcLineCount.Text = string.Empty;
            lblSrcTokenCount.Text = &quot;&quot;;
            lblParseTime.Text = &quot;&quot;;
            lblParseErrorCount.Text = &quot;&quot;;


            gridCompileErrors.Rows.Clear();

            Application.DoEvents();
        }

        private void ShowCompileStats()
        {
            lblSrcLineCount.Text = $&quot;Lines: {editTextBox.Lines.Count()} &quot;;
            lblSrcTokenCount.Text = $&quot;Tokens: {_parseTree.Tokens.Count()}&quot;;
            lblParseTime.Text = $&quot;Parse Time: {LastParseTime}ms&quot;;
            lblParseErrorCount.Text = _parseTree.HasErrors() ? $&quot;Errors: {_parseTree.ParserMessages.Count() }&quot; : &quot;No Errors&quot;;

        }

        /// &lt;summary&gt;
        /// Updates Compile Errors Gridview
        /// &lt;/summary&gt;
        private void ShowCompilerErrors()
        {
            gridCompileErrors.Rows.Clear();
            if (_parseTree == null || _parseTree.ParserMessages.Count == 0) return;
            foreach (var err in _parseTree.ParserMessages)
                gridCompileErrors.Rows.Add(err.Location, err, err.ParserState);
        }

        /// &lt;summary&gt;
        /// Allows to position over token at selected error.
        /// &lt;/summary&gt;
        /// &lt;param name=&quot;sender&quot;&gt;&lt;/param&gt;
        /// &lt;param name=&quot;e&quot;&gt;&lt;/param&gt;
        private void gridCompileErrors_CellDoubleClick(object sender, DataGridViewCellEventArgs e)
        {
            if (e.RowIndex &lt; 0 || e.RowIndex &gt;= gridCompileErrors.Rows.Count) return;
            var err = gridCompileErrors.Rows[e.RowIndex].Cells[1].Value as LogMessage;
            switch (e.ColumnIndex)
            {
                case 0: //state
                case 1: //stack top
                    ShowSourcePosition(err.Location.Position, 1);
                    break;
            }//switch
        }

        /// &lt;summary&gt;
        /// Shows a caret in editTextBox for a selected token
        /// &lt;/summary&gt;
        /// &lt;param name=&quot;position&quot;&gt;&lt;/param&gt;
        /// &lt;param name=&quot;length&quot;&gt;&lt;/param&gt;
        private void ShowSourcePosition(int position, int length)
        {
            if (position &lt; 0) return;
            editTextBox.SelectionStart = position;
            editTextBox.SelectionLength = length;
            //editTextBox.Select(location.Position, length);
            editTextBox.DoCaretVisible();
            editTextBox.Focus();

        }

        /// &lt;summary&gt;
        /// Parse code delayed after editing program.
        /// &lt;/summary&gt;
        /// &lt;param name=&quot;sender&quot;&gt;&lt;/param&gt;
        /// &lt;param name=&quot;e&quot;&gt;&lt;/param&gt;
        private void editTextBox_TextChangedDelayed(object sender, TextChangedEventArgs e)
        {
            ParseCode(false);

        }

        private void cmdRefresh_Click(object sender, EventArgs e)
        {
            RefreshCode();
        }

        /// &lt;summary&gt;
        /// Refresh, reload assigned code into editBox
        /// &lt;/summary&gt;
        public void RefreshCode()
        {

            editTextBox.Text = Code;

        }
        private void ProgramEditorForm_KeyDown(object sender, KeyEventArgs e)
        {
            if(ModifierKeys == Keys.Control)
            {
                switch (e.KeyCode)
                {
                    case Keys.Insert:
                        if(editTextBox.SelectedText != null)
                        {
                            ShowIdentifier(editTextBox.SelectedText);

                        }
                        break;
                    
                }
                e.Handled = true;
            }


            switch (e.KeyCode)
            {
                case Keys.F2:
                    SendCode(); e.Handled = true; break;
                case Keys.F4:
                    ClearCode(); e.Handled = true; break;
                case Keys.F6:
                    SaveFile(); e.Handled = true; break;
                case Keys.F7:
                    LoadFile(); e.Handled = true; break;
                case Keys.F8:
                    RefreshCode(); e.Handled = true; break;
                case Keys.F10:
                    LinesValidator(); e.Handled = true; break;

            }//switch.

        }

        private void ShowIdentifier(string selectedText)
        {
            frmIdentifierInfo frm = new frmIdentifierInfo();


            int PointIndex = 0;
            var TokenType = CoderHelper.GetTypeIdentifier(Identifiers, selectedText, out PointIndex);
            if (TokenType == PCODE_CONST.UNDEFINED_SYMBOL)
                return;
        

            frm.Text = selectedText;
            
            switch (TokenType)
            {
                case PCODE_CONST.OUTPOINTTYPE:
                    frm.Label.Text = Identifiers.Outputs[PointIndex].Label;
                    frm.FullLabel.Text = Identifiers.Outputs[PointIndex].FullLabel;
                    frm.Value.Text = Identifiers.Outputs[PointIndex].Value;
                    frm.Units.Text = Identifiers.Outputs[PointIndex].Units;
                    frm.AutoManual.Text = Identifiers.Outputs[PointIndex].AutoManual;
                    frm.ControlPointName.Text = Identifiers.Outputs[PointIndex].ControlPointName;
                    frm.ControlPointType.Text = &quot;OUTPUT&quot;;
                    break;
                case PCODE_CONST.INPOINTTYPE:
                    frm.Label.Text = Identifiers.Inputs[PointIndex].Label;
                    frm.FullLabel.Text = Identifiers.Inputs[PointIndex].FullLabel;
                    frm.Value.Text = Identifiers.Inputs[PointIndex].Value;
                    frm.Units.Text = Identifiers.Inputs[PointIndex].Units;
                    frm.AutoManual.Text = Identifiers.Inputs[PointIndex].AutoManual;
                    frm.ControlPointName.Text = Identifiers.Inputs[PointIndex].ControlPointName;
                    frm.ControlPointType.Text = &quot;INPUT&quot;;
                    break;
                case PCODE_CONST.VARPOINTTYPE:
                    frm.Label.Text = Identifiers.Variables[PointIndex].Label;
                    frm.FullLabel.Text = Identifiers.Variables[PointIndex].FullLabel;
                    frm.Value.Text = Identifiers.Variables[PointIndex].Value;
                    frm.Units.Text = Identifiers.Variables[PointIndex].Units;
                    frm.AutoManual.Text = Identifiers.Variables[PointIndex].AutoManual;
                    frm.ControlPointName.Text = Identifiers.Variables[PointIndex].ControlPointName;
                    frm.ControlPointType.Text = &quot;VARIABLE&quot;;
                    break;
                case PCODE_CONST.PID:
                    //TODO: Resolve what's a PID? Program Identifier?
                    break;
                default:
                    break;
            }


            frm.ShowDialog();



        }

        private void cmdLoad_Click(object sender, EventArgs e)
        {

            LoadFile();

        }

        /// &lt;summary&gt;
        /// Open file dialog to load a text file into editor
        /// &lt;/summary&gt;
        public void LoadFile()
        {
            // Create an instance of the open file dialog box.
            OpenFileDialog openFileDialog1 = new OpenFileDialog();

            // Set filter options and filter index.
            openFileDialog1.Filter = &quot;Text Files (.txt)|*.txt|All Files (*.*)|*.*&quot;;
            openFileDialog1.FilterIndex = 1;

            openFileDialog1.Multiselect = true;

            // Call the ShowDialog method to show the dialog box.
            DialogResult userClickedOK = openFileDialog1.ShowDialog();

            // Process input if the user clicked OK.
            if (userClickedOK == DialogResult.OK)
            {
                string text = System.IO.File.ReadAllText(openFileDialog1.FileName);

                editTextBox.Text = text;

            }
        }

        /// &lt;summary&gt;
        /// User call to SendCode event
        /// &lt;/summary&gt;
        /// &lt;param name=&quot;sender&quot;&gt;&lt;/param&gt;
        /// &lt;param name=&quot;e&quot;&gt;&lt;/param&gt;
        private void cmdSend_Click(object sender, EventArgs e)
        {
            SendCode();
        }



        /// &lt;summary&gt;
        /// Triggers SendCode Event
        /// &lt;/summary&gt;
        private void SendCode()
        {
            ParseCode(true); //Performs full parsing and semantic checks

            if (_parseTree.HasErrors() || _parseTree.ParserMessages.Any())
            {
                MessageBox.Show(&quot;Send operation, aborted&quot;, &quot;Error(s) found&quot;);
                return;
            }

            Code = editTextBox.Text;
            OnSend(new SendEventArgs(Code, Tokens));

        }

        private void cmdSave_Click(object sender, EventArgs e)
        {
            SaveFile();
        }

        /// &lt;summary&gt;
        /// Open File dialog to save a copy of program code into a file.
        /// &lt;/summary&gt;
        public void SaveFile()
        {
            // Create an instance of the open file dialog box.
            SaveFileDialog openFileDialog1 = new SaveFileDialog();

            // Set filter options and filter index.
            openFileDialog1.Filter = &quot;Text Files (.txt)|*.txt|All Files (*.*)|*.*&quot;;
            openFileDialog1.FilterIndex = 1;



            // Call the ShowDialog method to show the dialog box.
            DialogResult userClickedOK = openFileDialog1.ShowDialog();

            // Process input if the user clicked OK.
            if (userClickedOK == DialogResult.OK)
            {
                System.IO.File.WriteAllText(openFileDialog1.FileName, editTextBox.Text);

            }
        }


        private void cmdSettings_Click(object sender, EventArgs e)
        {
            EditSettings();
        }

        private void EditSettings()
        {



            SettingsBag.SelectedObject = editTextBox;
            SettingsBag.Top = editTextBox.Top;
            SettingsBag.Height = editTextBox.Height;
            SettingsBag.Left = editTextBox.Width - SettingsBag.Width;

            SettingsBag.Visible = !SettingsBag.Visible;


            ////NOT WORKING: Serialize SettingsBag;
            //IFormatter formatter = new BinaryFormatter();
            //Stream stream = new FileStream(&quot;EditorSettings.bin&quot;, FileMode.Create, FileAccess.Write, FileShare.None);
            //formatter.Serialize(stream, editTextBox  );
            //stream.Close();



        }

        private void ProgramEditorForm_ResizeEnd(object sender, EventArgs e)
        {
            if (SettingsBag.Visible)
            {
                SettingsBag.Top = editTextBox.Top;
                SettingsBag.Height = editTextBox.Height;
                SettingsBag.Left = editTextBox.Width - SettingsBag.Width;
            }
        }

        private void ProgramEditorForm_Resize(object sender, EventArgs e)
        {
            if (SettingsBag.Visible)
            {
                SettingsBag.Top = editTextBox.Top;
                SettingsBag.Height = editTextBox.Height;
                SettingsBag.Left = editTextBox.Width - SettingsBag.Width;
            }
        }

        private void cmdRenumber_Click(object sender, EventArgs e)
        {
            LinesValidator();
        }




        /// &lt;summary&gt;
        /// Pre-process tokens from parser
        /// &lt;/summary&gt;
        /// &lt;remarks&gt;Expressions are converted to RPN&lt;/remarks&gt;
        public void ProcessTokens()
        {

            string[] excludeTokens = { &quot;CONTROL_BASIC&quot;, &quot;LF&quot; };
            bool isFirstToken = true;
            var Cancel = false;

            int WaitCount = 0;

            try
            {
                Tokens = new List&lt;EditorTokenInfo&gt;();

                if (_parseTree == null) return;

                //foreach (var tok in _parseTree.Tokens)
                for (var idxToken = 0; idxToken &lt; _parseTree.Tokens.Count; idxToken++)
                {
                    var tok = _parseTree.Tokens[idxToken];
                    var tokentext = tok.Text;
                    var terminalname = tok.Terminal.Name;

                    switch (tok.Terminal.Name)
                    {

                        #region Comments
                        case &quot;Comment&quot;:
                            //split Comments into two tokens
                            Tokens.Add(new EditorTokenInfo(&quot;REM&quot;, &quot;REM&quot;));
                            Tokens.Last().Type = (short)LINE_TOKEN.REM;
                            Tokens.Last().Token = (short)LINE_TOKEN.REM;
                            var commentString = tok.Text.Substring(4).TrimEnd(' ');
                            Tokens.Add(new EditorTokenInfo(commentString, &quot;Comment&quot;));
                            Tokens.Last().Type = (short)commentString.Length;
                            Tokens.Last().Token = (short)LINE_TOKEN.STRING;
                            break;
                        #endregion

                        case &quot;PhoneNumber&quot;:
                            var PhoneString = tok.Text.TrimEnd(' ');
                            Tokens.Add(new EditorTokenInfo(PhoneString, &quot;PhoneNumber&quot;));
                            Tokens.Last().Type = (short)PhoneString.Length;
                            Tokens.Last().Token = (short)LINE_TOKEN.STRING;
                            break;

                        case &quot;IntegerNumber&quot;:
                            //rename to LineNumber only if first token on line.
                            Tokens.Add(new EditorTokenInfo(tokentext, isFirstToken ? &quot;LineNumber&quot; : terminalname));
                            break;

                        case &quot;LocalVariable&quot;:
                            EditorTokenInfo NewLocalVar = new EditorTokenInfo(tokentext, terminalname);
                            NewLocalVar.Type = (short)PCODE_CONST.LOCAL_VAR;
                            NewLocalVar.Token = (short)TYPE_TOKEN.IDENTIFIER;
                            Tokens.Add(NewLocalVar);
                            break;

                        #region Control Points Generics | Identifiers, before any expressions
                        //Before any expression, as in assigments
                        //Acá faltan varios tipos de identificadores, agregarlos posteriormente
                        //VARS | PIDS | WRS | ARS | OUTS | INS | PRG | GRP | DMON | AMON
                        case &quot;VARS&quot;:
                        case &quot;INS&quot;:
                        case &quot;OUTS&quot;:

                            string output = Regex.Match(tokentext, @&quot;\d+&quot;).Value;
                            int CtrlPointIndex = Convert.ToInt16(output) - 1; //VAR1 will get index 0, and so on.
                                                                              //Prepare token identifier to encode: Token + Index + Type
                            EditorTokenInfo CPIdentifier = new EditorTokenInfo(tokentext, tok.Terminal.Name);
                            switch (tok.Terminal.Name)
                            {
                                case &quot;VARS&quot;:
                                    CPIdentifier.Type = (short)PCODE_CONST.VARPOINTTYPE;
                                    break;
                                case &quot;INS&quot;:
                                    CPIdentifier.Type = (short)PCODE_CONST.INPOINTTYPE;
                                    break;
                                case &quot;OUTS&quot;:
                                    CPIdentifier.Type = (short)PCODE_CONST.OUTPOINTTYPE;
                                    break;
                                default:
                                    CPIdentifier.Type = (short)PCODE_CONST.UNDEFINED_SYMBOL;
                                    break;
                            }

                            CPIdentifier.Index = (short)CtrlPointIndex;
                            CPIdentifier.Token = (short)PCODE_CONST.LOCAL_POINT_PRG;
                            Tokens.Add(CPIdentifier);
                            break;

                        case &quot;PRG&quot;:
                            string idxPRG = Regex.Match(tokentext, @&quot;\d+&quot;).Value;
                            int CPIdx = Convert.ToInt16(idxPRG) - 1; //PRG1 will get index 0, and so on.
                                                                     //Prepare token identifier to encode: Index (single Byte)
                            EditorTokenInfo CPIdPRG = new EditorTokenInfo(tokentext, &quot;PRG&quot;);
                            CPIdPRG.Type = (short)TYPE_TOKEN.KEYWORD;
                            CPIdPRG.Index = (short)CPIdx;
                            CPIdPRG.Token = (short)PCODE_CONST.LOCAL_POINT_PRG;
                            Tokens.Add(CPIdPRG);
                            break;

                        case &quot;MRK&quot;: //termporary marker for commas between arguments, generated when
                            //encoding ARGCOUNT for CALL PRG
                            //Translated to EOE
                            Tokens.Add(new EditorTokenInfo(&quot;EOE&quot;, &quot;EOE&quot;));
                            Tokens.Last().Token = (short)LINE_TOKEN.EOE;

                            break;

                        case &quot;Identifier&quot;:
                            //Locate Identifier and Identify Token associated ControlPoint.
                            //To include this info in TokenInfo.Type and update TokenInfo.TerminalName
                            int PointIndex = 0;
                            var TokenType = CoderHelper.GetTypeIdentifier(Identifiers, tokentext, out PointIndex);
                            if (TokenType == PCODE_CONST.UNDEFINED_SYMBOL)
                            {
                                //There is a semantic error here
                                //Add error message to parser and cancel renumbering.
                                //Don't break it inmediately, to show all possible errors of this type
                                _parseTree.ParserMessages.Add(new LogMessage(ErrorLevel.Error,
                                    tok.Location,
                                    $&quot;Semantic Error: Undefined Identifier: {tok.Text}{System.Environment.NewLine}Check if PRG object is valid.&quot;,
                                    new ParserState(&quot;Validating Tokens&quot;)));
                                ShowCompilerErrors();
                                Cancel = true;
                            }
                            else
                            {
                                //Prepare token identifier to encode: Token + Index + Type
                                EditorTokenInfo NewIdentifier = new EditorTokenInfo(tokentext, terminalname);
                                NewIdentifier.Type = (short)TokenType;
                                NewIdentifier.Index = (short)PointIndex;
                                NewIdentifier.Token = (short)PCODE_CONST.LOCAL_POINT_PRG;
                                Tokens.Add(NewIdentifier);
                            }
                            break;

                        #endregion

                        #region Assigments and Expressions
                        case &quot;ASSIGN&quot;:

                            if (Tokens.Last().TerminalName == &quot;PRG&quot;)
                            {
                                //CALL PRG ASSIGMENT ARGS ...
                                //counter for identifiers as arguments
                                Tokens.Add(new EditorTokenInfo(&quot;ARGCOUNT&quot;, &quot;ARGCOUNT&quot;));

                                //count identifiers (arguments)
                                var ArgIdx = Tokens.Count - 1;
                                var idCnt = 0;
                                var NxtId = idxToken + 1;

                                while (_parseTree.Tokens[NxtId].Terminal.Name == &quot;Identifier&quot;
                                    || _parseTree.Tokens[NxtId].Terminal.Name == &quot;COMMA&quot;)
                                {
                                    if (_parseTree.Tokens[NxtId].Terminal.Name == &quot;Identifier&quot;)
                                    {
                                        //count this identifier
                                        idCnt++;
                                    }
                                    else
                                    {
                                        //It's a comma, change it to marker 0xFF
                                        _parseTree.Tokens[NxtId].Terminal.Name = &quot;MRK&quot;;
                                    }
                                    NxtId++;
                                }
                                //Also produce a new token here, last MRK = 0xFF
                                _parseTree.Tokens.Insert(NxtId, new Token(new Terminal(&quot;MRK&quot;), new SourceLocation(0, 0, 0), &quot;MRK&quot;, null));
                                Tokens[ArgIdx].Index = (short)idCnt;

                                break; //Only when ASSIGN found after  PRG
                            }

                            //Any other way, encode an assigment ↓ ↓ ↓ ↓ 
                            EditorTokenInfo assignToken, last;

                            var index = Tokens.Count - 1;
                            last = Tokens[index];
                            Tokens.RemoveAt(index);
                            assignToken = new EditorTokenInfo(tokentext, terminalname);
                            assignToken.Token = (short)LINE_TOKEN.ASSIGN;
                            //insert it before assignar var.
                            Tokens.Add(assignToken);
                            Tokens.Add(last);
                            //get the expression in postfix
                            functions = new Stack&lt;EditorTokenInfo&gt;();
                            ///////////////////////////////////////////////
                            // ALL FUNCTIONS AND LITERALS IN EXPRESSIONS
                            ///////////////////////////////////////////////
                            Tokens.AddRange(GetExpression(ref idxToken, ref Cancel));
                            //En caso que haya un then o un else en la pila
                            //extraer y poner un delimintador EOE
                            if (branches.Count &gt; 0)
                            {
                                switch (branches.Peek().TerminalName)
                                {
                                    case &quot;THEN&quot;:
                                    case &quot;ELSE&quot;:
                                        branches.Pop();
                                        Tokens.Add(new EditorTokenInfo(&quot;EOE&quot;, &quot;EOE&quot;));
                                        Tokens.Last().Token = (short)LINE_TOKEN.EOE;
                                        Tokens.Last().Index = 0;
                                        break;
                                    default:
                                        break;
                                }
                            }
                            break;
                        #endregion

                        #region Numeric Literals and Constants
                        case &quot;Number&quot;:
                        case &quot;CONNUMBER&quot;:
                        case &quot;TABLENUMBER&quot;:
                        case &quot;SYSPRG&quot;:
                        case &quot;TIMER&quot;:
                        case &quot;PANEL&quot;:
                            Tokens.Add(new EditorTokenInfo(tokentext, terminalname));
                            Tokens.Last().Token = (short)PCODE_CONST.CONST_VALUE_PRG;
                            Tokens.Last().Index = (short)Convert.ToInt16(tokentext);
                            break;

                        case &quot;TimeLiteral&quot;:
                            Tokens.Add(new EditorTokenInfo(tokentext, terminalname));
                            Tokens.Last().Token = (short)PCODE_CONST.CONST_VALUE_PRG;
                            Tokens.Last().Index = (short)Convert.ToInt16(tokentext);
                            Tokens.Last().Type = (short)FUNCTION_TOKEN.TIME_FORMAT;
                            break;


                        case &quot;PRT_A&quot;:
                        case &quot;PRT_B&quot;:
                        case &quot;PRT_0&quot;:
                        case &quot;ALL&quot;:
                            Tokens.Add(new EditorTokenInfo(tokentext, terminalname));
                            PRT_TOKEN PrtToken = (PRT_TOKEN)Enum.Parse(typeof(PRT_TOKEN), terminalname.ToString().Trim());
                            Tokens.Last().Token = (short)PrtToken;

                            break;
                        #endregion

                        #region IF IF+ IF- THEN ELSE
                        case &quot;IF&quot;:
                        case &quot;IF+&quot;:
                        case &quot;IF-&quot;:
                            EditorTokenInfo IfToken = new EditorTokenInfo(tokentext, terminalname);

                            LINE_TOKEN TypeToken = (LINE_TOKEN)Enum.Parse(typeof(LINE_TOKEN), terminalname.ToString().Trim());
                            IfToken.Token = (short)TypeToken;
                            IfToken.Precedence = 200;
                            Tokens.Add(IfToken);
                            branches.Push(IfToken);
                            var LastIdx = idxToken;
                            //GET IF CLAUSE
                            Tokens.AddRange(GetExpression(ref idxToken, ref Cancel));

                            break;

                        case &quot;THEN&quot;:
                            //START MARKER FOR THEN PART
                            Tokens.Add(new EditorTokenInfo(tokentext, terminalname));
                            Tokens.Last().Token = (short)LINE_TOKEN.EOE; //End marker for Expr.
                            Tokens.Last().Index = (short)Tokens.Count; //Next token will be OFFSET

                            if (branches.Count &gt; 0)
                            {
                                switch (branches.Peek().Text)
                                {
                                    case &quot;IF&quot;:
                                    case &quot;IF+&quot;:
                                    case &quot;IF-&quot;:
                                        branches.Pop();//Pop last IF*
                                        branches.Push(Tokens.Last()); //Push corresponding THEN
                                        break;
                                    default:
                                        break;
                                }

                            }

                            //Offset to be treated as a 2 bytes NUMBER
                            Tokens.Add(new EditorTokenInfo(&quot;OFFSET&quot;, &quot;OFFSET&quot;));
                            Tokens.Last().Token = 0;


                            break;

                        case &quot;ELSE&quot;:
                            //ELSE
                            Tokens.Add(new EditorTokenInfo(tokentext, terminalname));
                            Tokens.Last().Token = (short)LINE_TOKEN.ELSE; //End marker for Expr.

                            if (branches.Count &gt; 0)
                            {
                                switch (branches.Peek().Text)
                                {
                                    case &quot;THEN&quot;:

                                        branches.Pop();//Pop last THEN*

                                        break;
                                    default:
                                        break;
                                }

                            }

                            branches.Push(Tokens.Last()); //Push corresponding ELSE

                            //START MARKER FOR ELSE PART
                            Tokens.Add(new EditorTokenInfo(&quot;EOE&quot;, &quot;EOE&quot;));
                            Tokens.Last().Token = (short)LINE_TOKEN.EOE; //End marker for Expr.
                            Tokens.Last().Index = (short)Tokens.Count; //Next token will be OFFSET



                            //Offset to be treated as a NUMBER
                            Tokens.Add(new EditorTokenInfo(&quot;OFFSET&quot;, &quot;OFFSET&quot;));
                            Tokens.Last().Token = 0;

                            break;
                        #endregion

                        case &quot;LF&quot;:
                        case &quot;EOF&quot;:
                            if (branches.Count &gt; 0)
                            {
                                switch (branches.Peek().Text)
                                {
                                    case &quot;THEN&quot;:
                                    case &quot;ELSE&quot;:
                                        var offsetIdx = branches.Pop().Index;
                                        //references token with end marker 
                                        Tokens[offsetIdx].Index = (short)Tokens.Count;
                                        Tokens.Add(new EditorTokenInfo(&quot;EOE&quot;, &quot;EOE&quot;));
                                        Tokens.Last().Token = (short)LINE_TOKEN.EOE;
                                        break;
                                    default:
                                        break;
                                }
                            }

                            Tokens.Add(new EditorTokenInfo(tokentext, terminalname));

                            break;

                        #region Commands
                        //Simple Commands
                        case &quot;START&quot;:
                        case &quot;STOP&quot;:
                        case &quot;CLEAR&quot;:
                        case &quot;RETURN&quot;:
                        case &quot;HANGUP&quot;:
                        case &quot;GOTO&quot;:
                        case &quot;GOSUB&quot;:
                        case &quot;ON_ALARM&quot;:
                        case &quot;ON_ERROR&quot;:
                        case &quot;ENABLEX&quot;:
                        case &quot;DISABLEX&quot;:
                        case &quot;ENDPRG&quot;:
                        case &quot;RUN_MACRO&quot;:
                        case &quot;CALL&quot;:
                        case &quot;SET_PRINTER&quot;:
                        case &quot;PRINT_AT&quot;:
                        case &quot;ALARM_AT&quot;:
                        case &quot;PHONE&quot;:
                        case &quot;PRINT&quot;:

                            Tokens.Add(new EditorTokenInfo(tokentext, terminalname));
                            LINE_TOKEN SimpleToken = (LINE_TOKEN)Enum.Parse(typeof(LINE_TOKEN), terminalname.ToString().Trim());
                            Tokens.Last().Token = (short)SimpleToken;
                            break;

                        case &quot;DECLARE&quot;:

                            Tokens.Add(new EditorTokenInfo(tokentext, terminalname));
                            LINE_TOKEN DeclareToken = (LINE_TOKEN)Enum.Parse(typeof(LINE_TOKEN), terminalname.ToString().Trim());
                            Tokens.Last().Token = (short)DeclareToken;

                            Tokens.Add(new EditorTokenInfo(&quot;ARGCOUNT&quot;, &quot;ARGCOUNT&quot;));

                            //count identifiers (arguments)
                            var DeclareIdx = Tokens.Count - 1;
                            var idCount = 0;
                            var NextId = idxToken + 1;

                            while (_parseTree.Tokens[NextId].Terminal.Name == &quot;Identifier&quot;)
                            {
                                idCount++;
                                NextId++;
                            }
                            Tokens[DeclareIdx].Index = (short)idCount;


                            break;
                        case &quot;WAIT&quot;:
                            Tokens.Add(new EditorTokenInfo(tokentext, terminalname));
                            LINE_TOKEN WaitToken = (LINE_TOKEN)Enum.Parse(typeof(LINE_TOKEN), terminalname.ToString().Trim());
                            Tokens.Last().Token = (short)WaitToken;
                            Tokens.AddRange(GetExpression(ref idxToken, ref Cancel));
                            //Add EOE and counter
                            WaitCount++;
                            Tokens.Add(new EditorTokenInfo(&quot;WAITCOUNTER&quot;, &quot;WAITCOUNTER&quot;));
                            Tokens.Last().Token = (short)LINE_TOKEN.EOE;
                            Tokens.Last().Index = (short)WaitCount;

                            break;
                        #endregion

                        #region Defaults
                        case &quot;LET&quot;:
                        default: // No special cases, or expected to be ready to encode.
                            Tokens.Add(new EditorTokenInfo(tokentext, terminalname));
                            Console.WriteLine($&quot;ProcessTokens(): TOKEN TerminalName:{terminalname}-Text:{tokentext} passed by defautl&quot;);
                            break;
                            #endregion
                    }
                    isFirstToken = terminalname == &quot;LF&quot; ? true : false;

                }
            }
            catch (Exception ex)
            {
                ExceptionHandler.Show(ex, &quot;ProcessTokens()&quot;);
                ex = null;
            }


        }




        /// &lt;summary&gt;
        /// Parse tokens from infix notation into postfix (RPN)
        /// &lt;/summary&gt;
        /// &lt;param name=&quot;Index&quot;&gt;Start Index&lt;/param&gt;
        /// &lt;param name=&quot;Cancel&quot;&gt;Cancel processing because of at least one semantic error&lt;/param&gt;
        /// &lt;returns&gt;RPN Expression, ready to be encoded&lt;/returns&gt;
        public List&lt;EditorTokenInfo&gt; GetExpression(ref int Index, ref bool Cancel)
        {
            // _parseTree.Tokens.Count
            List&lt;EditorTokenInfo&gt; Expr = new List&lt;EditorTokenInfo&gt;();
            Stack&lt;EditorTokenInfo&gt; Oper = new Stack&lt;EditorTokenInfo&gt;();


            try
            {
                //Last processed token was a BEGIN EXPRESSION MARKER
                Index++; //Jump over next token.

                for (; Index &lt; _parseTree.Tokens.Count; Index++)
                {
                    var tok = _parseTree.Tokens[Index];
                    var tokentext = tok.Text;
                    var terminalname = tok.Terminal.Name;


                    switch (terminalname)
                    {

                        #region PARENTHESIS

                        case &quot;(&quot;:
                            //If the incoming symbol is a left parenthesis, push it on the stack.
                            Oper.Push(new EditorTokenInfo(tokentext, terminalname));
                            break;

                        case &quot;)&quot;:
                            //	If the incoming symbol is a right parenthesis, 
                            // pop the stack and print the operators until you see a left parenthesis. 
                            // Discard the pair of parentheses.
                            if (Oper.Count &gt; 0)
                            {
                                while (Oper.Peek().TerminalName != &quot;(&quot;)
                                {
                                    Expr.Add(Oper.Pop());
                                }
                            }
                            if (Oper.Count &gt; 0) Oper.Pop(); //Discard left parenthesis
                                                            //see if those parenthesis were parts of a function call.
                            if (Oper.Count &gt; 0 &amp;&amp; Oper.Peek().Precedence == 200)
                            {
                                //Function Call
                                //Add function token to expression.
                                Expr.Add(Oper.Pop());
                                if (functions.Count &gt; 0)
                                {
                                    if (Expr.Last().TerminalName == functions.Peek().TerminalName)
                                    {
                                        //Add the counter into Index property of token function

                                        Expr.Last().Index = functions.Peek().Index;
                                        functions.Pop();
                                    }

                                }

                            }
                            break;

                        #endregion

                        case &quot;COMMA&quot;:
                            //Add 1 to counter of subexpressions, comma means here comes another one.
                            if (functions.Count &gt; 0) functions.Peek().Index++;
                            //Save everything down to Left Parenthesis but don't discard it
                            if (Oper.Count &gt; 0)
                            {
                                while (Oper.Peek().TerminalName != &quot;(&quot;)
                                {
                                    Expr.Add(Oper.Pop());
                                }
                            }
                            break;

                        #region END MARKERS FOR EXPRESSION
                        case &quot;LF&quot;:
                        case &quot;THEN&quot;:
                        case &quot;EOF&quot;:
                        case &quot;REM&quot;:
                        case &quot;ELSE&quot;:


                            //Pop all operators remaining in stack.
                            //Return expression
                            while (Oper.Count &gt; 0)
                            {
                                Expr.Add(Oper.Pop());
                            }

                            Index--; //Get back, this token should be processed by parent function.
                            return Expr;
                        #endregion

                        #region Identifier
                        //TODO: NEW: PIDS debe ir acá: Acá faltan varios tipos de identificadores, agregarlos posteriormente
                        case &quot;VARS&quot;:
                        case &quot;INS&quot;:
                        case &quot;OUTS&quot;:
                        case &quot;PRG&quot;:
                            string output = Regex.Match(tokentext, @&quot;\d+&quot;).Value;
                            int CtrlPointIndex = Convert.ToInt16(output) - 1; //VAR1 will get index 0, and so on.
                                                                              //Prepare token identifier to encode: Token + Index + Type
                            EditorTokenInfo CPIdentifier = new EditorTokenInfo(tokentext, &quot;Identifier&quot;);
                            switch (terminalname)
                            {
                                case &quot;VARS&quot;:
                                    CPIdentifier.Type = (short)PCODE_CONST.VARPOINTTYPE;
                                    break;
                                case &quot;INS&quot;:
                                    CPIdentifier.Type = (short)PCODE_CONST.INPOINTTYPE;
                                    break;
                                case &quot;OUTS&quot;:
                                    CPIdentifier.Type = (short)PCODE_CONST.OUTPOINTTYPE;
                                    break;
                                default:
                                    CPIdentifier.Type = (short)PCODE_CONST.UNDEFINED_SYMBOL;
                                    break;
                            }

                            CPIdentifier.Index = (short)CtrlPointIndex;
                            CPIdentifier.Token = (short)PCODE_CONST.LOCAL_POINT_PRG;
                            Expr.Add(CPIdentifier);
                            break;

                        case &quot;Identifier&quot;:
                            //Locate Identifier and Identify Token associated ControlPoint.
                            //To include this info in TokenInfo.Type and update TokenInfo.TerminalName
                            int PointIndex = 0;
                            var TokenType = CoderHelper.GetTypeIdentifier(Identifiers, tokentext, out PointIndex);
                            if (TokenType == PCODE_CONST.UNDEFINED_SYMBOL)
                            {
                                //There is a semantic error here
                                //Add error message to parser and cancel renumbering.
                                //Don't break it inmediately, to show all possible errors of this type
                                _parseTree.ParserMessages.Add(new LogMessage(ErrorLevel.Error,
                                    tok.Location,
                                    $&quot;Semantic Error: Undefined Identifier: {tok.Text}&quot;,
                                    new ParserState(&quot;Validating Tokens&quot;)));
                                ShowCompilerErrors();
                                Cancel = true;
                            }
                            else
                            {
                                //Prepare token identifier to encode: Token + Index + Type
                                EditorTokenInfo NewIdentifier = new EditorTokenInfo(tokentext, terminalname);
                                NewIdentifier.Type = (short)TokenType;
                                NewIdentifier.Index = (short)PointIndex;
                                NewIdentifier.Token = (short)PCODE_CONST.LOCAL_POINT_PRG;
                                Expr.Add(NewIdentifier);
                            }
                            break;

                        #endregion

                        #region OPERATORS

                        case &quot;PLUS&quot;:
                        case &quot;MINUS&quot;:
                        case &quot;MUL&quot;:
                        case &quot;DIV&quot;:
                        case &quot;POW&quot;:
                        case &quot;MOD&quot;:
                        case &quot;LT&quot;:
                        case &quot;GT&quot;:
                        case &quot;LE&quot;:
                        case &quot;GE&quot;:
                        case &quot;EQ&quot;:
                        case &quot;NE&quot;:
                        case &quot;AND&quot;:
                        case &quot;XOR&quot;:
                        case &quot;OR&quot;:
                        case &quot;NOT&quot;:
                        case &quot;ASSIGN&quot;:

                            //All operators are cast directly into token of TYPE_TOKEN and with precedence attribute.
                            //To allow further transforms by RPN Parser of Expressions
                            if(tokentext == &quot;=&quot; &amp;&amp; terminalname == &quot;ASSIGN&quot;)
                            {
                                terminalname = &quot;EQ&quot;;
                            }
                            var op = new EditorTokenInfo(tokentext, terminalname);
                            TYPE_TOKEN TypeToken = (TYPE_TOKEN)Enum.Parse(typeof(TYPE_TOKEN), terminalname.ToString().Trim());
                            op.Token = (short)TypeToken;
                            op.Precedence = (short)tok.KeyTerm.Precedence;

                            if (Oper.Count == 0)
                            {
                                Oper.Push(op);
                            }
                            else
                            {
                                while (Oper.Count &gt; 0 &amp;&amp; op.Precedence &lt;= Oper.Peek().Precedence)
                                {
                                    Expr.Add(Oper.Pop());
                                }

                                Oper.Push(op);
                            }
                            break;
                        #endregion

                        #region Number
                        case &quot;Number&quot;:
                        case &quot;CONNUMBER&quot;:
                        case &quot;TABLENUMBER&quot;:
                        case &quot;SYSPRG&quot;:
                        case &quot;TIMER&quot;:
                            Expr.Add(new EditorTokenInfo(tokentext, terminalname));
                            Expr.Last().Token = (short)PCODE_CONST.CONST_VALUE_PRG;
                            //Possible use to dif from TimeLiteral
                            //Expr.Last().Type = (short)PCODE_CONST.CONST_VALUE_PRG;

                            break;
                        case &quot;TimeLiteral&quot;:
                            //NEW: See if a TIME FORMAT VALUE

                            Expr.Add(new EditorTokenInfo(tokentext, terminalname));
                            Expr.Last().Token = (short)PCODE_CONST.CONST_VALUE_PRG;
                            Expr.Last().Type = (short)FUNCTION_TOKEN.TIME_FORMAT;
                            break;
                        #endregion

                        #region FUNCTIONS
                        case &quot;ABS&quot;:
                        case &quot;INTERVAL&quot;:
                        case &quot;_INT&quot;:
                        case &quot;LN&quot;:
                        case &quot;LN_1&quot;:
                        case &quot;SQR&quot;:
                        case &quot;_Status&quot;:
                        case &quot;TBL&quot;:
                        case &quot;CONPROP&quot;:
                        case &quot;CONRATE&quot;:
                        case &quot;CONRESET&quot;:
                        case &quot;TIME&quot;:
                        case &quot;TIME_ON&quot;:
                        case &quot;TIME_OFF&quot;:
                        case &quot;WR_ON&quot;:
                        case &quot;WR_OFF&quot;:
                        case &quot;DOY&quot;:
                        case &quot;DOM&quot;:
                        case &quot;DOW&quot;:
                        case &quot;POWER_LOSS&quot;:
                        case &quot;UNACK&quot;:
                        case &quot;SCANS&quot;:
                        case &quot;USER_A&quot;:
                        case &quot;USER_B&quot;:


                        #region Functions with variable list of expressions, must add count of expressions as last token.
                        case &quot;AVG&quot;:
                        case &quot;MAX&quot;:
                        case &quot;MIN&quot;:

                            //All operators are cast directly into token of TYPE_TOKEN and with precedence attribute.
                            //To allow further transforms by RPN Parser of Expressions
                            var fxToken = new EditorTokenInfo(tokentext, terminalname);
                            FUNCTION_TOKEN tokenValue = (FUNCTION_TOKEN)Enum.Parse(typeof(FUNCTION_TOKEN), terminalname.ToString().Trim());
                            fxToken.Token = (short)tokenValue;

                            //fx.Precedence = (short)tok.KeyTerm.Precedence;
                            fxToken.Precedence = 200;
                            fxToken.Index = 1; //At least one expression to count
                            if (Oper.Count == 0)
                            {
                                Oper.Push(fxToken);
                                functions.Push(fxToken);

                            }
                            else
                            {
                                while (Oper.Count &gt; 0 &amp;&amp; fxToken.Precedence &lt;= Oper.Peek().Precedence)
                                {
                                    Expr.Add(Oper.Pop());
                                }

                                Oper.Push(fxToken);
                                functions.Push(fxToken);

                            }
                            break;
                            #endregion

                            #endregion
                    }

                }

                //Pop All operators remaining in stack.
                while (Oper.Count &gt; 0)
                {
                    Expr.Add(Oper.Pop());
                }

                //Check: If Expr.Count &lt; 1 then semantic error found, expected Expression.
                Index -= 1;
            }
            catch (Exception ex)
            {
                ExceptionHandler.Show(ex, &quot;GetExpression() found an exception&quot;);
            }

            return Expr;
        }
    }

}</code></pre>
</div>
</div>

</div>

</article>
</div>

</div>
</div>
</div>

</body>
</html>
