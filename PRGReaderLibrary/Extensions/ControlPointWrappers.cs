<!DOCTYPE html>
<html lang='en'>
<head>
<meta charset='utf-8'>
<meta content='GitLab Community Edition' name='description'>
<title>
t3000/PRGReaderLibrary/Extensions/ControlPointWrappers.cs at 04d1a0c6fd995bb0b730114d3ed87357ad1188aa - C programming / T3000 | 
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
  GitLab.GfmAutoComplete.dataSource = "/c-programming/t3000/autocomplete_sources?type=NilClass&type_id=04d1a0c6fd995bb0b730114d3ed87357ad1188aa%2FPRGReaderLibrary%2FExtensions%2FControlPointWrappers.cs"
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
<input id="path" name="path" type="hidden" value="PRGReaderLibrary/Extensions/ControlPointWrappers.cs" />
</form>


</div>
<div class='tree-holder' id='tree-holder'>
<ul class='breadcrumb repo-breadcrumb'>
<li>
<i class='icon-angle-right'></i>
<a href="/c-programming/t3000/tree/04d1a0c6fd995bb0b730114d3ed87357ad1188aa">t3000
</a></li>
<li>
<a href="/c-programming/t3000/tree/04d1a0c6fd995bb0b730114d3ed87357ad1188aa/PRGReaderLibrary">PRGReaderLibrary</a>
</li>
<li>
<a href="/c-programming/t3000/tree/04d1a0c6fd995bb0b730114d3ed87357ad1188aa/PRGReaderLibrary/Extensions">Extensions</a>
</li>
<li>
<a href="/c-programming/t3000/blob/04d1a0c6fd995bb0b730114d3ed87357ad1188aa/PRGReaderLibrary/Extensions/ControlPointWrappers.cs"><strong>
ControlPointWrappers.cs
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
ControlPointWrappers.cs
<small>9.02 KB</small>
</span>
<span class='options hidden-xs'><div class='btn-group tree-btn-group'>
<span class='btn btn-small disabled'>edit</span>
<a class="btn btn-small" href="/c-programming/t3000/raw/04d1a0c6fd995bb0b730114d3ed87357ad1188aa/PRGReaderLibrary/Extensions/ControlPointWrappers.cs" target="_blank">raw</a>
<a class="btn btn-small" href="/c-programming/t3000/blame/04d1a0c6fd995bb0b730114d3ed87357ad1188aa/PRGReaderLibrary/Extensions/ControlPointWrappers.cs">blame</a>
<a class="btn btn-small" href="/c-programming/t3000/commits/04d1a0c6fd995bb0b730114d3ed87357ad1188aa/PRGReaderLibrary/Extensions/ControlPointWrappers.cs">history</a>
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
</a></div>
<div class='highlight'>
<pre><code class='language-cs'>﻿using ExceptionHandling;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PRGReaderLibrary.Extensions
{
    /// &lt;summary&gt;
    /// Enumerable Identifiers Types
    /// &lt;/summary&gt;
    public enum IdentifierTypes
    {
        VARS, INS, OUTS, PRGS, SCHS, HOLS
    }

    /// &lt;summary&gt;
    /// Basic info for controlpoint identifiers
    /// &lt;/summary&gt;
    public class ControlPointInfo
    {
        //Identifier Info
        public string Label { get; set; } = &quot;&quot;;
        public string FullLabel { get; set; } = &quot;&quot;;
        public string ControlPointName { get; set; } = &quot;&quot;;
        public string Value { get; set; } = &quot;&quot;;
        public string Units { get; set; } = &quot;&quot;;
        public string AutoManual { get; set; } = &quot;&quot;;

        //ControlPoint Type
        public IdentifierTypes Type { get; set; } = IdentifierTypes.VARS;

        /// &lt;summary&gt;
        /// Default constructor
        /// &lt;/summary&gt;
        public ControlPointInfo() { }

               
    }

    /// &lt;summary&gt;
    /// List of all enumerables identifiers/controlpoints
    /// &lt;/summary&gt;
    public class ControlPoints
    {

        #region Lists of ControlPoints
        /// &lt;summary&gt;
        /// Variables identifiers
        /// &lt;/summary&gt;
        public List&lt;ControlPointInfo&gt; Variables { get; set; } = new List&lt;ControlPointInfo&gt;();

        /// &lt;summary&gt;
        /// Inputs identifiers
        /// &lt;/summary&gt;
        public List&lt;ControlPointInfo&gt; Inputs { get; set; } = new List&lt;ControlPointInfo&gt;();

        /// &lt;summary&gt;
        /// Outputs identifiers
        /// &lt;/summary&gt;
        public List&lt;ControlPointInfo&gt; Outputs { get; set; } = new List&lt;ControlPointInfo&gt;();

        /// &lt;summary&gt;
        /// Programs Identifiers
        /// &lt;/summary&gt;
        public List&lt;ControlPointInfo&gt; Programs { get; set; } = new List&lt;ControlPointInfo&gt;();


        /// &lt;summary&gt;
        /// Schedules identifiers
        /// &lt;/summary&gt;
        public List&lt;ControlPointInfo&gt; Schedules { get; set; } = new List&lt;ControlPointInfo&gt;();

        /// &lt;summary&gt;
        /// Holidays identifiers
        /// &lt;/summary&gt;
        public List&lt;ControlPointInfo&gt; Holidays { get; set; } = new List&lt;ControlPointInfo&gt;();

        #endregion

        /// &lt;summary&gt;
        /// Add a variable control point info
        /// &lt;/summary&gt;
        /// &lt;param name=&quot;variable&quot;&gt;VariablePoint&lt;/param&gt;
        /// &lt;param name=&quot;index&quot;&gt;Index&lt;/param&gt;
        public void Add(VariablePoint variable, int index)
        {

            try
            {
                ControlPointInfo newCPInfo = new ControlPointInfo
                {
                    ControlPointName = &quot;VAR&quot; + index,
                    Label = variable.Label,
                    FullLabel = variable.Description,
                    Type = IdentifierTypes.VARS,
                    Value = variable.Value.ToString(),
                    Units = &quot;UNIT&quot;,
                    AutoManual = variable.AutoManual == 0 ? &quot;Auto&quot; : &quot;Manual&quot;
                };


                Variables.Add(newCPInfo);
            }
            catch (Exception ex)
            {
                ExceptionHandler.Show(ex, &quot;Addition of new Variable to ControlPointsInfo&quot;);
            }

        }


        /// &lt;summary&gt;
        /// Add a Input control point info
        /// &lt;/summary&gt;
        /// &lt;param name=&quot;input&quot;&gt;Input Point&lt;/param&gt;
        /// &lt;param name=&quot;index&quot;&gt;Index&lt;/param&gt;
        public void Add(InputPoint input, int index)
        {

            try
            {
                ControlPointInfo newCPInfo = new ControlPointInfo
                {
                    ControlPointName = &quot;IN&quot; + index,
                    Label = input.Label,
                    FullLabel = input.Description,
                    Type = IdentifierTypes.INS,
                    Value = &quot;UNIT&quot;,
                    AutoManual = input.AutoManual == 0 ? &quot;Auto&quot; : &quot;Manual&quot;
                };


                Inputs.Add(newCPInfo);
            }
            catch (Exception ex)
            {
                ExceptionHandler.Show(ex, &quot;Addition of new Input to ControlPointsInfo&quot;);
            }

        }

        /// &lt;summary&gt;
        /// Add Output control point info
        /// &lt;/summary&gt;
        /// &lt;param name=&quot;output&quot;&gt;Output Point&lt;/param&gt;
        /// &lt;param name=&quot;index&quot;&gt;Index&lt;/param&gt;
        public void Add(OutputPoint output, int index)
        {

            try
            {
                ControlPointInfo newCPInfo = new ControlPointInfo
                {
                    ControlPointName = &quot;OUT&quot; + index,
                    Label = output.Label,
                    FullLabel = output.Description,
                    Type = IdentifierTypes.OUTS,
                    Value = &quot;UNIT&quot;,
                    AutoManual = output.AutoManual == 0 ? &quot;Auto&quot; : &quot;Manual&quot;
                };


                Outputs.Add(newCPInfo);
            }
            catch (Exception ex)
            {
                ExceptionHandler.Show(ex, &quot;Addition of new Output to ControlPointsInfo&quot;);
            }

        }


        /// &lt;summary&gt;
        /// Add Program control point info
        /// &lt;/summary&gt;
        /// &lt;param name=&quot;program&quot;&gt;Program Point&lt;/param&gt;
        /// &lt;param name=&quot;index&quot;&gt;Index&lt;/param&gt;
        public void Add(ProgramPoint program, int index)
        {

            try
            {
                ControlPointInfo newCPInfo = new ControlPointInfo
                {
                    ControlPointName = &quot;PRG&quot; + index,
                    Label = program.Label,
                    FullLabel = program.Description,
                    Type = IdentifierTypes.PRGS,
                    Value = &quot;UNIT&quot;,
                    AutoManual = program.AutoManual == 0 ? &quot;Auto&quot; : &quot;Manual&quot;
                };


                Outputs.Add(newCPInfo);
            }
            catch (Exception ex)
            {
                ExceptionHandler.Show(ex, &quot;Addition of new Program to ControlPointsInfo&quot;);
            }

        }


        /// &lt;summary&gt;
        /// Add Schedule control point info
        /// &lt;/summary&gt;
        /// &lt;param name=&quot;schedule&quot;&gt;Schedule Point&lt;/param&gt;
        /// &lt;param name=&quot;index&quot;&gt;Index&lt;/param&gt;
        public void Add(SchedulePoint schedule, int index)
        {

            try
            {
                ControlPointInfo newCPInfo = new ControlPointInfo
                {
                    ControlPointName = &quot;SCH&quot; + index,
                    Label = schedule.Label,
                    FullLabel = schedule.Description,
                    Type = IdentifierTypes.SCHS,
                    Value = &quot;UNIT&quot;,
                    AutoManual = schedule.AutoManual == 0 ? &quot;Auto&quot; : &quot;Manual&quot;
                };

                Outputs.Add(newCPInfo);
            }
            catch (Exception ex)
            {
                ExceptionHandler.Show(ex, &quot;Addition of new Schedule to ControlPointsInfo&quot;);
            }

        }


        /// &lt;summary&gt;
        /// Add Holiday control point info
        /// &lt;/summary&gt;
        /// &lt;param name=&quot;holiday&quot;&gt;Holiday Point&lt;/param&gt;
        /// &lt;param name=&quot;index&quot;&gt;Index&lt;/param&gt;
        public void Add(HolidayPoint holiday, int index)
        {

            try
            {
                ControlPointInfo newCPInfo = new ControlPointInfo
                {
                    ControlPointName = &quot;HOL&quot; + index,
                    Label = holiday.Label,
                    FullLabel = holiday.Description,
                    Type = IdentifierTypes.HOLS,
                    Value = &quot;UNIT&quot;,
                    AutoManual = holiday.AutoManual == 0 ? &quot;Auto&quot; : &quot;Manual&quot;
                };

                Outputs.Add(newCPInfo);
            }
            catch (Exception ex)
            {
                ExceptionHandler.Show(ex, &quot;Addition of new Holiday to ControlPointsInfo&quot;);
            }

        }

        /// &lt;summary&gt;
        /// Default constructor;
        /// &lt;/summary&gt;
        public ControlPoints() { }

        /// &lt;summary&gt;
        /// Builds a copy from PRG Control Points
        /// &lt;/summary&gt;
        /// &lt;param name=&quot;prg&quot;&gt;PRG object&lt;/param&gt;
        public ControlPoints(Prg prg)
        {

            try
            {
                int i;
                //Copy variables info
                for (i = 0; i &lt; prg.Variables.Count(); i++)
                    Add(prg.Variables[i], i+1);
                //Copy inputs info
                for (i = 0; i &lt; prg.Inputs.Count(); i++)
                    Add(prg.Inputs[i], i+1);
                //Copy outputs info
                for (i = 0; i &lt; prg.Outputs.Count(); i++)
                    Add(prg.Outputs[i], i+1);
                //Copy programs info
                for (i = 0; i &lt; prg.Programs.Count(); i++)
                    Add(prg.Programs[i], i+1);
                //Copy schedules info
                for (i = 0; i &lt; prg.Schedules.Count(); i++)
                    Add(prg.Schedules[i], i+1);
                //Copy holidays info
                for (i = 0; i &lt; prg.Holidays.Count(); i++)
                    Add(prg.Holidays[i], i+1);
            }
            catch (Exception ex)
            {
                ExceptionHandler.Show(ex, &quot;Copying Control Points&quot;);
            }


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
