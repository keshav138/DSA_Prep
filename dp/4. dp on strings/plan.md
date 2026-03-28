# Pre-Work: What You Need to Know BEFORE Starting

## ✅ Must Know BEFORE Day 1 (Spend 2-3 days on this)

### **1. Django Fundamentals** (You mentioned you've learned this already)
- Models, Views, Templates (MVT pattern)
- URL routing
- Forms and ModelForms
- Django ORM basics (queries, filters, relationships)
- User authentication (built-in User model)
- Migrations
- Admin panel

### **2. PostgreSQL Basics** (1 day to familiarize)
**What to learn:**
- Difference between PostgreSQL and SQLite
- Basic SQL commands (SELECT, JOIN, WHERE, GROUP BY)
- How to install PostgreSQL locally
- Connection setup with Django (`psycopg2` adapter)
- pgAdmin or DBeaver for database visualization

**Resources:**
- Install PostgreSQL: https://www.postgresql.org/download/
- Django + PostgreSQL setup: https://docs.djangoproject.com/en/5.0/ref/databases/#postgresql-notes
- 30-min crash course: Search "PostgreSQL tutorial for beginners" on YouTube

**You'll learn as you go:** Indexing, query optimization, complex joins

---

### **3. Django REST Framework Basics** (1-2 days)
**What to learn:**
- What APIs are and why they matter
- Serializers (converting Django models to JSON)
- ViewSets and APIViews
- Routers for URL generation
- Basic authentication (TokenAuthentication)

**Resources:**
- Official DRF tutorial: https://www.django-rest-framework.org/tutorial/quickstart/
- YouTube: "Django REST Framework Course" by Traversy Media or Dennis Ivy

**You'll learn as you go:** Permissions, pagination, filtering, throttling

---

### **4. Git & GitHub Workflow** (If not already comfortable)
**What to know:**
- Basic commands: `git init`, `add`, `commit`, `push`, `pull`
- Branching strategy (main/dev branches)
- `.gitignore` for Django projects
- Writing good commit messages
- Creating a proper README

**Resources:**
- Git in 15 mins: https://www.youtube.com/watch?v=USjZcfj8yxE

---

## 🔄 Learn As You Go (Don't stress about these now)

### **1. Redis**
- You'll learn when implementing caching (Day 9-10)
- Concept: In-memory key-value store for fast data access
- Just know: It's like a super-fast temporary database
- Installation is simple, integration with Django is straightforward

### **2. Django Channels (WebSockets)**
- You'll learn on Day 11-12
- Concept: Enables real-time bidirectional communication
- Django has great docs for this
- Pusher (alternative) is even easier if Channels feels complex

### **3. Celery (Background Tasks)**
- Optional for your project, can skip if time is tight
- You'll understand when you need to send emails without blocking requests

### **4. Docker**
- Learn during deployment (Day 16-17)
- Concept: Packages your app with all dependencies
- Many tutorials available, and deployment platforms provide templates

### **5. AWS S3 / Cloudinary**
- Learn when implementing file uploads (Day 13-14)
- Cloudinary is easier for beginners (simpler API)

---

## 📚 Quick Setup Checklist (Do this before Day 1)

```bash
# 1. Install Python 3.10+ if not already
python --version

# 2. Install PostgreSQL
# Download from postgresql.org

# 3. Create a virtual environment
python -m venv venv
source venv/bin/activate  # On Windows: venv\Scripts\activate

# 4. Install core dependencies
pip install django djangorestframework psycopg2-binary python-decouple

# 5. Test PostgreSQL connection
# Create a test database in pgAdmin or terminal
```

---

# 📅 18-DAY ROADMAP (Day-by-Day Breakdown)

## **Phase 1: Foundation (Days 1-4)**

### **Day 1: Project Setup & Database Design**
**Goal:** Get the skeleton ready

**Tasks:**
1. Create Django project: `django-admin startproject taskmaster`
2. Create app: `python manage.py startapp tasks`
3. Set up PostgreSQL database locally
4. Configure `settings.py`:
   ```python
   DATABASES = {
       'default': {
           'ENGINE': 'django.db.backends.postgresql',
           'NAME': 'taskmaster_db',
           'USER': 'your_username',
           'PASSWORD': 'your_password',
           'HOST': 'localhost',
           'PORT': '5432',
       }
   }
   ```
5. Design database schema on paper/draw.io:
   - **User** (Django's built-in)
   - **Project** (name, description, created_by, team_members)
   - **Task** (title, description, project, assigned_to, status, priority, due_date)
   - **Comment** (task, user, text, timestamp)
   - **Activity** (project, user, action, timestamp)

**Deliverable:** Empty Django project connected to PostgreSQL with schema design document

---

### **Day 2: Core Models & Admin Panel**
**Goal:** Build your database models

**Tasks:**
1. Create models in `tasks/models.py`:
   ```python
   class Project(models.Model):
       name = models.CharField(max_length=200)
       description = models.TextField()
       created_by = models.ForeignKey(User, on_delete=CASCADE)
       team_members = models.ManyToManyField(User, related_name='projects')
       created_at = models.DateTimeField(auto_now_add=True)
   
   class Task(models.Model):
       STATUS_CHOICES = [('TODO', 'To Do'), ('IN_PROGRESS', 'In Progress'), ...]
       # ... rest of fields
   ```

2. Run migrations: `python manage.py makemigrations && python manage.py migrate`
3. Register models in `admin.py`
4. Create superuser: `python manage.py createsuperuser`
5. Add 2-3 sample projects and tasks via admin panel

**Deliverable:** Working admin panel with relationships visible

**Learning resources if stuck:**
- Django models documentation
- YouTube: "Django Models Tutorial"

---

### **Day 3: User Authentication & Registration**
**Goal:** Users can sign up and log in

**Tasks:**
1. Create authentication endpoints:
   - `/api/auth/register/` (POST)
   - `/api/auth/login/` (POST)
   - `/api/auth/logout/` (POST)
   - `/api/auth/user/` (GET - current user info)

2. Install: `pip install djangorestframework-simplejwt`
3. Configure JWT authentication in `settings.py`
4. Create serializers for User model
5. Write views for registration/login
6. Test with Postman or Thunder Client (VS Code extension)

**Deliverable:** Working authentication via API (get JWT tokens)

**If stuck:** DRF authentication tutorial, JWT documentation

---

### **Day 4: CRUD for Projects**
**Goal:** Full CRUD operations for projects

**Tasks:**
1. Create `ProjectSerializer` with nested team members
2. Create `ProjectViewSet` with DRF:
   ```python
   class ProjectViewSet(viewsets.ModelViewSet):
       queryset = Project.objects.all()
       serializer_class = ProjectSerializer
       permission_classes = [IsAuthenticated]
   ```

3. Implement:
   - List all projects (GET `/api/projects/`)
   - Create project (POST)
   - Retrieve single project (GET `/api/projects/{id}/`)
   - Update project (PUT/PATCH)
   - Delete project (DELETE)
   - Add/remove team members (custom action)

4. Test all endpoints in Postman
5. Add permission checks (only creators can delete)

**Deliverable:** Full CRUD for projects with proper permissions

**Common issues:** Serializer nested relationships - check DRF docs on writable nested serializers

---

## **Phase 2: Core Features (Days 5-8)**

### **Day 5: CRUD for Tasks**
**Goal:** Task management within projects

**Tasks:**
1. Create `TaskSerializer`
2. Create `TaskViewSet` with filtering:
   - Filter by project: `/api/tasks/?project=1`
   - Filter by status: `/api/tasks/?status=TODO`
   - Filter by assigned user: `/api/tasks/?assigned_to=2`
3. Implement task assignment logic
4. Add validation (due_date must be future, etc.)
5. Create custom actions:
   - `/api/tasks/{id}/change_status/` (POST)
   - `/api/tasks/{id}/assign/` (POST)

**Deliverable:** Working task CRUD with smart filtering

---

### **Day 6: Comments & Activity Feed**
**Goal:** Task comments and project activity tracking

**Tasks:**
1. Create `Comment` model and serializer
2. Nested comments under tasks: `/api/tasks/{id}/comments/`
3. Create `ActivityLog` model (auto-logs actions)
4. Use Django signals to create activity logs:
   ```python
   @receiver(post_save, sender=Task)
   def log_task_creation(sender, instance, created, **kwargs):
       if created:
           Activity.objects.create(...)
   ```
5. Endpoint: `/api/projects/{id}/activity/` (recent activities)

**Deliverable:** Comments working, activity feed tracking all changes

**Learning:** Django signals documentation

---

### **Day 7: Search, Filters & Pagination**
**Goal:** Make the API production-ready

**Tasks:**
1. Install: `pip install django-filter`
2. Add search functionality:
   ```python
   filter_backends = [SearchFilter, DjangoFilterBackend, OrderingFilter]
   search_fields = ['title', 'description']
   ```
3. Add pagination in `settings.py`:
   ```python
   REST_FRAMEWORK = {
       'DEFAULT_PAGINATION_CLASS': 'rest_framework.pagination.PageNumberPagination',
       'PAGE_SIZE': 20
   }
   ```
4. Advanced filters:
   - Tasks due this week
   - Overdue tasks
   - My assigned tasks
5. Add ordering: `/api/tasks/?ordering=-created_at`

**Deliverable:** Searchable, filterable, paginated API

---

### **Day 8: API Documentation & Testing**
**Goal:** Document your API professionally

**Tasks:**
1. Install: `pip install drf-yasg` (Swagger/OpenAPI)
2. Configure Swagger UI at `/api/docs/`
3. Add docstrings to all viewsets
4. Write unit tests for critical endpoints:
   ```python
   class TaskAPITest(APITestCase):
       def test_create_task(self):
           # ... test code
   ```
5. Test authentication, permissions, edge cases
6. Create a Postman collection (export and add to GitHub)

**Deliverable:** Browsable API docs, basic test coverage

---

## **Phase 3: Advanced Features (Days 9-12)**

### **Day 9: Redis Setup & Caching**
**Goal:** Speed up your app with caching

**Tasks:**
1. Install Redis locally:
   - macOS: `brew install redis`
   - Ubuntu: `sudo apt install redis`
   - Windows: Use Docker or WSL
2. Install: `pip install redis django-redis`
3. Configure Django cache in `settings.py`:
   ```python
   CACHES = {
       'default': {
           'BACKEND': 'django_redis.cache.RedisCache',
           'LOCATION': 'redis://127.0.0.1:6379/1',
       }
   }
   ```
4. Implement caching:
   - Cache project list: `@method_decorator(cache_page(60*5))`
   - Cache user's project count
   - Invalidate cache on updates
5. Test cache behavior (check Redis with `redis-cli`)

**Deliverable:** Faster API responses with Redis caching

**Learning:** "Django + Redis tutorial" on YouTube

---

### **Day 10: Session Management & Rate Limiting**
**Goal:** Secure and limit API usage

**Tasks:**
1. Use Redis for session storage
2. Install: `pip install django-ratelimit`
3. Add rate limiting:
   ```python
   @ratelimit(key='user', rate='100/h', method='POST')
   def create_task(request):
       # ...
   ```
4. Different limits for different endpoints
5. Return proper 429 responses when rate limited
6. Store user sessions in Redis (faster than DB)

**Deliverable:** Rate-limited API with Redis-backed sessions

---

### **Day 11: Real-Time Updates - Part 1 (Setup)**
**Goal:** Prepare for WebSocket integration

**Choose one approach:**

**Option A: Django Channels (More learning, better for CV)**
1. Install: `pip install channels channels-redis`
2. Configure `settings.py` and `asgi.py`
3. Create basic WebSocket consumer
4. Test connection with WebSocket client

**Option B: Pusher (Faster implementation)**
1. Sign up for free Pusher account
2. Install: `pip install pusher`
3. Configure credentials
4. Test basic push notification

**Deliverable:** WebSocket connection established (no features yet)

**Learning:** Django Channels official tutorial OR Pusher quickstart

---

### **Day 12: Real-Time Updates - Part 2 (Implementation)**
**Goal:** Live task updates across users

**Tasks:**
1. Trigger real-time events on:
   - Task created
   - Task status changed
   - Task assigned
   - New comment added
2. Frontend receives updates via WebSocket
3. Create a simple HTML/JS page to test:
   ```javascript
   const ws = new WebSocket('ws://localhost:8000/ws/project/1/');
   ws.onmessage = (event) => {
       console.log('Update:', JSON.parse(event.data));
   };
   ```
4. Test with multiple browser tabs (simulate multiple users)

**Deliverable:** Real-time task updates working

**This is your "wow" feature - spend extra time polishing this**

---

## **Phase 4: Polish & Deployment (Days 13-18)**

### **Day 13: File Uploads (Optional but Recommended)**
**Goal:** Users can attach files to tasks

**Tasks:**
1. Choose storage:
   - **Easy:** Cloudinary (free 25GB)
   - **Industry standard:** AWS S3 (free tier)
2. Install: `pip install cloudinary` or `pip install boto3 django-storages`
3. Add `FileField` to Task model
4. Configure media settings
5. Update serializers to handle file uploads
6. Test uploading images/PDFs via API

**Deliverable:** Working file attachment feature

**Skip if time is tight - focus on deployment instead**

---

### **Day 14: Permissions & Role-Based Access**
**Goal:** Proper authorization (who can do what)

**Tasks:**
1. Create custom permissions:
   ```python
   class IsProjectMember(BasePermission):
       def has_object_permission(self, request, view, obj):
           return request.user in obj.project.team_members.all()
   ```
2. Implement roles:
   - **Admin:** Can delete project, remove members
   - **Member:** Can create/edit tasks
   - **Viewer:** Read-only access
3. Add `role` field to Project-User relationship (ManyToMany through model)
4. Enforce permissions on all endpoints
5. Test with different user roles

**Deliverable:** Secure API with proper access control

---

### **Day 15: Frontend (Basic UI)**
**Goal:** Simple frontend to demo your API

**Option 1: Django Templates + HTMX (Recommended for speed)**
1. Create basic templates for:
   - Login/Register
   - Project list
   - Task board (Kanban-style with columns)
   - Task detail view
2. Use HTMX for dynamic updates (no page refresh)
3. Style with Tailwind CDN (no build step)

**Option 2: React/Vue (If you know it)**
1. Create separate frontend repo
2. Consume your API
3. Focus on task board view

**Deliverable:** Working UI to showcase your API

**Alternative:** Skip frontend entirely and use Swagger docs + Postman demo video

---

### **Day 16: Deployment Preparation**
**Goal:** Make app deployment-ready

**Tasks:**
1. Create `requirements.txt`: `pip freeze > requirements.txt`
2. Environment variables setup:
   ```python
   # Use python-decouple
   from decouple import config
   SECRET_KEY = config('SECRET_KEY')
   DEBUG = config('DEBUG', default=False, cast=bool)
   ```
3. Create `.env.example` file
4. Update `settings.py` for production:
   - `DEBUG = False`
   - `ALLOWED_HOSTS = ['your-domain.com']`
   - `SECURE_SSL_REDIRECT = True`
5. Create `Procfile` for deployment
6. Static files configuration
7. Database migration script

**Deliverable:** Production-ready configuration

---

### **Day 17: Deployment (Railway/Render)**
**Goal:** Live app on the internet

**Using Railway (Recommended):**
1. Sign up: https://railway.app
2. Create new project → Deploy from GitHub
3. Add PostgreSQL database (one-click)
4. Add Redis (one-click)
5. Set environment variables in dashboard
6. Deploy! Railway auto-detects Django
7. Run migrations via Railway CLI
8. Test deployed app

**Alternative: Render.com** (similar process)

**Tasks:**
- Get a custom domain or use Railway subdomain
- Test all endpoints on live server
- Check Redis and PostgreSQL connections
- Monitor logs for errors

**Deliverable:** Live URL you can share

**Common issues:** CORS, static files, WebSocket config - Railway docs have solutions

---

### **Day 18: Documentation & Demo**
**Goal:** Make it portfolio-ready

**Tasks:**
1. Write comprehensive README.md:
   - Project description
   - Features list
   - Tech stack with badges
   - Architecture diagram (use draw.io)
   - Setup instructions
   - API documentation link
   - Screenshots/GIFs
   - Live demo link
2. Record demo video (2-3 minutes):
   - Show real-time updates
   - Create task, assign it, change status
   - Multiple users interacting simultaneously
   - Highlight Redis caching (show response times)
3. Clean up code:
   - Remove debug prints
   - Add comments to complex logic
   - Format with `black` formatter
4. Add to GitHub with proper `.gitignore`
5. Update your CV with this project!

**Deliverable:** Portfolio-ready project with stunning README

---

## 🚨 IMPORTANT NOTES

### **If You Fall Behind:**
- **Skip Days 13-14** (file uploads, advanced permissions) - nice-to-haves
- **Simplify Day 11-12** (use Pusher instead of Channels)
- **Skip frontend** (Day 15) - Swagger docs are enough
- **Focus on:** Core CRUD + Real-time + Deployment

### **Daily Commitment:**
- 4-6 hours/day minimum
- Don't aim for perfection - aim for completion
- Deploy broken features and fix them live

### **Resources Hub:**
- Django docs: https://docs.djangoproject.com
- DRF docs: https://www.django-rest-framework.org
- Railway docs: https://docs.railway.app
- Stack Overflow: Your best friend

### **Red Flags to Avoid:**
- ❌ Hardcoded credentials (use `.env`)
- ❌ No `.gitignore` (don't commit `venv/`, `.env`)
- ❌ Poor README (this is what recruiters see first)
- ❌ Not deploying (broken deployment > no deployment)

---

## 🎯 SUCCESS METRICS

By Day 18, you should have:
- ✅ Fully functional CRUD API with authentication
- ✅ Real-time task updates (your standout feature)
- ✅ PostgreSQL + Redis integration
- ✅ Deployed on Railway/Render with custom domain
- ✅ Professional README with demo video
- ✅ 80%+ of the features working
- ✅ Updated CV with impressive bullet points

---

**Ready to start? Begin with the pre-work, then ping me on Day 1 morning and I'll help you troubleshoot setup issues. You've got this! 💪**

Want me to create starter code templates or a GitHub repo structure for you?
