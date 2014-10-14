prependtoblog
=============

My disturbing, proprietary, and inflexible blogging tool written in C for [twoseven.ca](http://www.twoseven.ca) (a [tilde.club](http://tilde.club/) clone) to teach myself file IO and perhaps to motivate me to keep a simple blog.

## Usage

```shell
$ prependtoblog <blogpost> <existing_blog>
```

Where `blogpost` is a plaintext file where the first line is the post title and the subsequent lines form paragraphs at the line break.

Here's what your `exisiting_blog` should look like:

```html
<html>
  <head>...</head>
  <body>
    <div class="container">
      <h1>Blog Title</h1>
      <!-- entry -->
      <div class="entry">
        <h2>Entry Title</h2>
        <p class="post-date">Saturday December 25 1999 at 04:16:02 PM (GMT-5:00)</p>
       
        <p>This is the body of the blog post. Lorem ipsum dolor sit amet.</p>
        <p>This is a new paragraph because a newline was in the original document.</p>
      </div>
      <!-- end entry -->
    </div>
  </body>
</html>
```

The next blogpost will be inserted immediately before the first occurence of `<!-- entry -->`. To get started, either write your first blogpost from scratch, or just add your own `<!-- entry -->` to your desired insertion point. I tried to keep the output code as clean as possible, but if you're not using 2-space indentation you're gonna have a bad time.
